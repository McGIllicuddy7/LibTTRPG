use std::f32::consts::PI;

pub use crate::imaglib::math::*;
use crate::{imaglib::{draw::colors::{DARK_RED, RED}, math}, Color, Image, Shader};
pub struct VecField{
    pub width:usize, 
    pub height:usize, 
    pub values:Box<[Vec2r]>
}
pub fn make_vector_field(width:usize, height:usize)->VecField{
    let mut values = Vec::new();
    values.reserve_exact(width*height);
    for _ in 0..width*height{
        values.push(rand_vec2r());
    }
    VecField { width, height, values: values.into_boxed_slice() }
}
impl VecField{
    pub fn new(width:usize, height:usize)->Self{
        make_vector_field(width, height)
    }
    pub fn get(&self, x:usize, y:usize)->Vec2r{
        self.values[y*self.width+x]
    }
    pub fn get_mut(&mut self, x:usize, y:usize)->&mut Vec2r{
        &mut self.values[y*self.width+x]
    }
    pub fn draw(&self, image:&mut Image,w:f32,s:f32 ,color:Color){
        let wr =image.width/self.width;
        let hr = image.height/self.height;
        for y in 0..self.height{
            for x in 0..self.width{
                let v = self.get(x, y);
                let yp = y*hr;
                let xp = x*wr;
                let loc = Vec2::new(xp as i32, yp as i32);
                image.draw_vec2r(loc, v, w, s, color);
            }
        }
    }
}
#[derive(Clone)]
pub struct Node{
    pub connections:Vec<usize>, 
    pub pos:Vec2r,
}
struct BShader{

}
static SHADER:BShader = BShader{};
impl Shader for BShader{
    fn kernel(&self,_screen_location:Vec2, _text_coord:Vec2r)->Color {
        DARK_RED
    }
}
#[derive(Clone)]
pub struct Building{
    pub loc:Vec2r, 
    pub theta:f32,
    pub dims:Vec2,
}
impl Building{
    pub fn draw(&self, image:&mut Image){
        image.draw_rect_rot(self.loc.x as i32, self.loc.y as i32, self.dims.x, self.dims.y, self.theta as f64, &SHADER);
    }
    pub fn max_dim(&self)->f32{
        let dims = self.dims;
        if dims.x>dims.y{
            dims.x as f32
        } else{
            dims.y as f32
        }
    }
    pub fn min_dim(&self)->f32{
        let dims = self.dims;
        if dims.x>dims.y{
            dims.y as f32
        } else{
            dims.x as f32
        }
    }
}
pub struct City{
    pub nodes:Vec<Node>,
    pub buildings:Vec<Building>,
    pub w:i32, 
    pub h:i32
}
pub fn cent_rand(mul:f32)->f32{
    let v0 = (rand_float()) as f32;
    ((v0-0.5)*mul*0.5)+mul/2.0
}
impl City{
    pub fn new(width:i32, height:i32, count:i32)->Self{
        let mut values = Vec::new();
        let dx = width/count;
        let dy = height/count;
        for x in 0..dx{
            for y in 0..dy{
                let px = (x*count) as f32;
                let py = (y*count) as f32;
                let rv = rand_vec2r()*0.4*dx as f32;
                let v = Vec2r::new(px,py)+rv;
                let n = Node{pos:v, connections:Vec::new()};
                values.push(n);
            
            }
        }
        /*for _ in 0..count*count*2{
            let p =Vec2::new(rand() as i32 %width, rand() as i32 %height).to_real();
            let n = Node{connections:Vec::new(), pos:p};
            values.push(n);
        } */
        City{nodes:values, buildings:Vec::new(),w:width, h:height}
    }
    pub fn line_intersects_building(&self, start:Vec2r, end:Vec2r)->Option<usize>{
        for j in 0..self.buildings.len(){
            let i = &self.buildings[j];
            let d = i.max_dim();
            let p = i.loc;
            if math::dist_to_line(start, end, p)<d{
                return Some(j);
            }
        }
        None
    }
    pub fn building_intersects_line(&self, building:&Building)->bool{
        let p = building.loc;
        let d = building.max_dim();
        for i in &self.nodes{
            for ip in &i.connections{
                let j = unsafe{self.nodes.get_unchecked(*ip)};
                let start =i.pos;
                let end = j.pos;
                if math::dist_to_line(start, end, p)<d{
                    return true;
                }
            }
        }
        false
    }
    pub fn building_intersects_building(&self, b:&Building)->bool{
        let md1 = b.max_dim();
        let bloc = b.loc;
        for i in& self.buildings{
            let md2 = i.min_dim();
            let del = i.loc.dist(bloc).sqrt();
            if del<(md1+md2)/2.0-0.25{
                return true;
            }
        } 
        false
    }
    pub fn place_buildings(&mut self,start:Vec2r, direction:Vec2r, len:f32){
        let mut count =0.0;
        let theta = direction.angle();
        while count<len{
            let mut rcount =0;
            let mut dt:i32;
            let mut delt:f32;
            loop{
                dt = if rand()%3 <=2 {
                    if rcount<8{
                        (rand_int()%4+8)as i32
                    } 
                    else if rcount<8{
                        (5)as i32
                    }
                    else{
                        1
                    }
                }else {
                    2
                };
                delt = 11.+dt as f32;
                let dx = 10+dt;
                let dy = 10+dt+(rand()%2) as i32;
                let dims = Vec2{x:dx, y:dy};
                let b = Building{loc:start+direction*count, theta:theta,dims:dims};
                if !self.building_intersects_line(&b){
                    if !self.building_intersects_building(&b){
                        self.buildings.push(b);
                        break;
                    } else if rcount<10{
                        rcount+=1;
                        continue;
                    }
                }else if rcount<10{
                    rcount+=1;
                    continue;
                }
                break;
            }
            count+= delt;
        }
    }
    pub fn update_build(&mut self, i:usize, count:usize)->bool{
        let mut candidates = Vec::new();
        let p0 = self.nodes[i].pos;
        for j in i+1..self.nodes.len(){
            let p1 = self.nodes[j].pos;
            if self.nodes[j].connections.len()>5{
                continue;
            }
            if p1.dist(p0).sqrt()>count as f32*25.0{
                continue;
            }
            if self.nodes[i].connections.contains(&j){
                continue;
            }
            while let Some(k) = self.line_intersects_building(p0, p1){
                if rand()%4==0 {
                    self.buildings.remove(k);
                }else{
                    break;
                }
           
            }
            candidates.push(j);
        }
        if candidates.len() == 0{
            return false;
        }
        while candidates.len() != 0{
            let idx = rand()%candidates.len() as u64;
            let n = candidates[idx as usize];
            candidates.remove(idx as usize);
            let p1 = self.nodes[n].pos;
            let del = p1-p0;
            let dl = del.len();
            let dln = del/dl;
            let dt = 12.0;
            self.place_buildings(p0+dln.rotate(PI/2.0)*(dt) as f32,dln, dl);
            self.place_buildings(p0+dln.rotate(-PI/2.0)*(dt) as f32,dln, dl);
            self.nodes[i].connections.push(n);
            self.nodes[n].connections.push(i);
            if rand()%2 == 0{break;}
        }

        self.nodes[i].connections.len()>(rand()%4) as usize
    }
    pub fn purge(&mut self){
        let mut outv = Vec::new();
        let w = self.w as f64/2.0;
        let c = Vec2r::new(w as f32, w as f32);
        for i in &self.buildings{
            let d = i.loc.dist(c).sqrt() as f64;
            if d>w+(rand_float()-0.5)*w { 
                if rand_float()*rand_float()*rand_float()*rand_float()*(w+100.)< d{
                    continue;
                }
            }
            let mut hit = false;
            for j in &self.nodes{
                if hit{
                    break;
                }
                for k in &j.connections{
                    let p0 = j.pos;
                    let p1 = self.nodes[*k].pos;
                    let p2 = i.loc;
                    if dist_to_line(p0, p1, p2)<2.{
                        hit = true;
                        break;
                    }
                }
            }
            if !hit{
                let mut k = i.clone();
                if k.dims.x<18{
                    k.dims.x+=1;
                }
                if k.dims.y<18{
                    k.dims.y+=1;
                }
                outv.push(k);
            }


        }
        self.buildings = outv;
    }
    pub fn build(&mut self){
        for i in 0..self.nodes.len(){
            let mut count = 0;
            loop{
                if self.update_build(i, count){
                    break;
                }
                count+=1;
               // println!("count:{count}, {i}");
                if count>20{
                    break;
                }
            }
        }
        self.purge();
        println!("building_count:{}",self.buildings.len())
    }
    pub fn draw(&self, image:&mut Image, color:Color, should_draw:bool){
        if should_draw{
            for i in 0..self.nodes.len(){
                let p = self.nodes[i].pos;
                image.draw_circ(self.nodes[i].pos.to_int(), 10, color);
                let cons = &self.nodes[i].connections;
                for j in cons{
                    let v = self.nodes[*j].pos;
                    image.draw_line(p.to_int(), v.to_int(),1.0, color);
                }
            }
        }
        for i in &self.buildings{
            i.draw(image);
        }
    }
}