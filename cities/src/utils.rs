use std::{error::Error, f64::consts:: TAU, fmt::Display, ops::Mul, sync::atomic::AtomicI64};

use rand::random_range;


#[derive(Debug, Clone)]
pub struct Grid<T>{
    values:Box<[T]>,
    height:usize, 
    width:usize,
}
#[derive(Debug)]
pub struct InvalidGridDimensions{
}
impl Display for InvalidGridDimensions{
    fn fmt(&self, f: &mut std::fmt::Formatter<'_>) -> std::fmt::Result {
        f.write_str("invalid grid dimensions")
    }
}
impl Error for InvalidGridDimensions{

}
impl<T> Grid<T>{
    pub fn new<U:Into<Box<[T]>>>(values:U, height:usize, width:usize)->Self{
        let t = values.into();
        assert!(height*width ==t.len());
        Self{values:t, height, width}
    }
    pub fn new_from_grid<U:ExactSizeIterator<Item = T>, V:ExactSizeIterator<Item = U>>(in_values:V)->Self{
        let height =in_values.len();
        let mut width = 0;
        let mut values = Vec::new();
        let mut first = true;
        values.reserve_exact(height*width);
        for i in in_values{
            if first{
                width = i.len();
            } else if width != i.len(){
                assert_eq!(width, i.len());
            }
            first = false;
            for j in i{
                values.push(j);
            }
        }
        Self { values:values.into(), height, width }
    }
    pub fn new_failable<U:Into<Box<[T]>>>(values:U, height:usize, width:usize)->Result<Self, InvalidGridDimensions>{
        let t = values.into();
        if height*width !=t.len(){
            return Err(InvalidGridDimensions {  })
        } else{
            Ok(Self{values:t, height, width})
        }

    }
    pub fn new_from_grid_failable<U:ExactSizeIterator<Item = T>, V:ExactSizeIterator<Item = U>>(in_values:V)->Result<Self, InvalidGridDimensions>{
        let height =in_values.len();
        let mut width = 0;
        let mut values = Vec::new();
        let mut first = true;
        values.reserve_exact(height*width);
        for i in in_values{
            if first{
                width = i.len();
            } else if i.len() != width{
                return Err(InvalidGridDimensions{})
            }
            first = false;
            for j in i{
                values.push(j);
            }
        }
        Ok(Self { values:values.into(), height, width })
    }
    pub fn get(&self,x:usize, y:usize)->&T{
        assert!(x<self.width && y<self.height);
        unsafe{
            self.values.get_unchecked(self.width*y+x)
        }
    }
    pub fn set(&mut self, x:usize, y:usize, v:T){
        assert!(x<self.width && y<self.height);
        unsafe{
            *self.values.get_unchecked_mut(self.width*y+x) = v
        }
    }
    pub fn height(&self)->usize{
        self.height
    }
    pub fn width(&self)->usize{
        self.width
    }

}
impl <T:Send+Sync>Grid<T>{
    pub fn shader<'a>(&'a mut self, kernel:&'a (impl (Fn(usize, usize,&T)->T)+Sync)){
        let _ = std::thread::scope(|scope|{
           // let sz = self.height/std::thread::available_parallelism().unwrap();
           let sz = self.height/16;
            let values = self.values.chunks_mut(self.width*sz);
            let mut y = 0;
            let width = self.width;
            for t in values{
                let func =move ||{
                    let ln = t.len();
                    for dy in 0..sz{
                        for x in 0..width{
                            if (dy)*width+x>=ln{
                                break;
                            }
                            let ptr = unsafe{t.get_unchecked_mut(dy*width+x)};
                            let v = kernel(x,y+dy, ptr);
                            *ptr = v;
                
                        }
                    }

                };
                y+= sz;
                scope.spawn(func);
            }
        });



    }
}

#[derive(Debug)]
pub struct NoiseRing{
    length:f64,
    values:Vec<f64>,
}
impl NoiseRing {
    pub fn random_float()->f64{
        const AMOUNT:i32 = 100_000_000;
        let base:i32 = random_range(0..AMOUNT);
        return base as f64/AMOUNT as f64;
    }
    pub fn new(length:f64, depth:usize)->Self{
        fn subdivide(values:&[f64],idx:i32)->Vec<f64>{
            let mut out = Vec::new();
            let mul = (2<<idx) as f64;
            for i in 0..values.len(){
                out.push(values[i]);
                if i <values.len()-1{
                    let tmp = NoiseRing::random_float()*2.-1.;
                    let v = (values[i]+values[i+1])/2.;
                    let vt = tmp/(mul*2.)+v;
                    out.push(if vt>1.{1.} else if vt<0.{0.} else{vt});
                }
            }
            return out;
        }
        let mut values = vec![];
        for _ in 0..8{
            values.push(Self::random_float());
        }
        for i in 0..depth{
            values = subdivide(&values,i as i32);
        }
        let mut max = 0.0;
        for i in &values{
            if *i>max{
                max = *i;
            }
        }
        for i in &mut values{
            *i/= max;
        }
        let out = Self { length, values };
        println!("{:#?}", out);
        out
    }
    pub fn sample(&self, idx:f64)->f64{
        let idx0 = idx;
        let l = self.length as f64;
        let v = idx/l;
        let idx = (v as f64 *(self.values.len()) as f64) as usize % self.values.len();
        let idx2 = (((v+1 as f64) *(self.values.len())as f64) as usize).rem_euclid(self.values.len());
       // println!("{idx0},{idx}, {idx2}");
        let lrp = idx0 as f64 - idx as f64 ;
        let v1 = self.values[idx];
        let v2 = self.values[idx2];
        let out = lerp(v1, v2, lrp);
        out
    }
}
pub fn lerp<V,T:Mul<f64, Output = T>+std::ops::Add<T, Output = V>>(l:T, r:T, v:f64)->V{
    l*(1.-v)+r*v
}
pub fn angle<T:Into<f64>>(x:T, y:T)->f64{
    let x0 = x.into();
    let y0 = y.into();
    let dist = (x0*x0+y0*y0).sqrt();
    if dist == 0.{
        return 0.
    }
    let x= x0/dist;
    let y= y0/dist;
    let mut out = f64::atan2(x, y);
    if out<0.{
        out = TAU+out
    }
    assert!(out<=TAU && out>=0.);
    out
}
pub fn angle_from<T:Into<f64>>(x:T, y:T, origin_x:T, origin_y:T)->f64{
    angle(x.into()-origin_x.into(), y.into()-origin_y.into())
}