//
//  Primal.h
//  Pathfinder_Character_Generator
//
//  Created by Isaac Hartin Pasco on 7/7/23.
//

#ifndef Primal_h
#define Primal_h
#pragma once
#include <vector>
#include <string>
using namespace std;
vector<string> Primal_Cantrips = {"Acid Splash", "Approximate", "Dancing Lights", "Detect Magic", "Disrupt Undead", "Electric Arc", "Gale Blast", "Gouging Claw", "Guidance",
"Healing Plaster", "Inside Ropes", "Invoke True Name", "Know Direction", "Light", "Prestidigitation", "Produce Flame", "Protect Companion", "Puff of Poison", "Ray of Frost",
"Read Aura", "Scatter Scree", "Sigil", "Spout", "Stabilize", "Tame", "Tanglefoot"};

vector<string> Primal_1st_Level = {"Acidic Burst", "Air Bubble", "Airburst", "Alarm", "Animal Allies", "Ant Haul","Aqueous Blast", "Breadcrumbs", "Briny Bolt",
"Buffeting Winds", "Burning Hands","Charm", "Chilling Spray", "Create Water", "Detect Poison", "Elysian Whimsy", "Fear",  "Feather Fall","Fleet Step", "Goblin Pox",
"Grease",  "Gritty Wheeze", "Gust of Wind", "Heal", "Helpful Steps", "Horizon Thunder Sphere","Hydraulic Push","Inkshot", "Jump", "Juvenile Companion", "Longstrider",
"Lose the Path", "Magic Fang", "Magic Stone", "Mending", "Mud Pit", "Negate Aroma", "Nettleskin", "Noxious Vapors", "Pass Without Trace", "Personal Rain Cloud", "Pest Form",
"Pet Cache", "Protector Tree", "Pummeling Rubble","Purify Food and Drink", "Purifiying Icicle", "Quick Sort", "Restyle", "Scorching Blast", "Scouring Sand", "Seashell of Stolen Sound",
"Shattering Gem", "Shillelagh", "Shocking Grasp", "Shockwave", "Snowball", "Spider Sting","Summon Animal", "Summon Fey", "Summon Plant or Fungus", "Swampcall","Synchronize",
"Tether", "Ventriloquism", "Verdant Sprout","Verminous Lure"};

vector<string>  Primal_2nd_Level = {"Acid Arrow", "Advanced Scurvy", "Animal Form", "Animal Messenger", "Ash Cloud", "Barkskin", "Blazing Blade", "Bone Spray" "Boneshaker",
"Bralani Referendom", "Breath of Drought", "Clawsong", "Continual Flame", "Create Food", "Dancing Shield", "Darkness", "Darkvision", "Deafness", "Dismantle", "Dispel Magic",
"Elemental Zone", "Endure Elements", "Enhance Victuals", "Enlarge", "Entangle", "Erase Trail", "Expeditious Excavation", "Extract Poison", "Faerie Fire","Fear the Sun",
"Feast of Ashes", "Feral Shades", "Final Sacrifice", "Flame Wisp","Flaming Sphere", "Fungal Hyphae", "Fungal Infestation", "Gentle Repose", "Glitterdust", "Guiding Star",
"Heat Metal", "Humanoid Form", "Ignite Fireworks","Impart Empathy", "Instant Armor", "Iron Gut", "Lock Item", "Loose Time's Arrow","Magnetic Attraction", "Magnetic Repulsion",
"Obscuring Mist", "Pack Attack", "Phantom Steed", "Quench", "Radiant Field", "Rapid Adaption", "Reaper's Lantern", "Remove Fear", "Remove Paralysis", "Resist Energy", "Restoration",
"Restore Senses", "Rime Slick",  "Scorching Ray", "Sea Surge", "Shape Wood", "Shatter", "Shrink", "Slough Skin", "Speak with Animals","Spider Climb", "Status", "Sudden Blight",
"Sudden Bolt", "Summon Elemental", "Summoner's Precaution", "Summoner's Visage", "Thundering Dominance", "Tree Shape", "Vomit Swarm","Water Breathing", "Water Walk",
"Web", "Worm's Repast"};

vector<string> Primal_3rd_Level = {"Animal Vision", "Aquesous Orb", "Blazing Dive", "Blindness", "Bottomless Stomach", "Caster's Imposition", "Crashing Wave",
"Cup of Dust", "Curse of Lost time", "Cyclone Rondo", "Day's Weight", "Dividing Trench", "Earthbind", "Elemental Absorption", "Elemental Anhiliation Wave", "Envenom Companion",
"Familiar's Face", "Far Sight", "Feet to Fins", "FireBall", "Gasping Marsh", "Glyph of Warding", "Haste", "Insect Form", "LIfe Connection", "Life Pact", "Lightning Bolt",
"Mad Monkeys", "Magnetic Acceleration", "Martyr's Intervetion", "Meld into Stone", "Mind of Menace", "Moonlight Ray", "Moth's Supper", "Neutralize Poison","Nondetection",
"Oneiric Mire", "Organsight", "Painted Scout", "Pillar of Water", "Positive Attunment", "Remove Disease", "Safe Passage", "Searing Light", "Shadow Spy", "Shifting Sand",
"Show the Way", "Slow", "Soothing Blossoms", "Stinking Cloud","Threefold Aspect", "Useasonable Squall", "Wall of Radiance", "Wall of Thorns", "Wall of Water", "Wall of Wind",
"Warding Agression", "Web of Eyes"};

vector<string> Primal_4th_Level = { "Aerial Form", "Air Walk", "Bestial Curse", "Bloodspray Curse", "Bursting Bloom", "Call the Blood", "Cloak of Light","Compel True Name",
"Coral Eruption", "Countless Eyes", "Creation", "Dinosaur Form", "Draw the Lightning", "Elemental Gift", "Elephant Form", "Enhance Senses", "Fey FOrm", "Fire Shield", "Fly",
"Freedom of Movement", "Gaseous Form", "Hallucinatory Terrain", "Hydralic Torrent", "Ice Storm", "Movanic Glimmer", "Murderous Vine", "Ocular Overload", "Petal Storm",
"Radiant Beam", "Radiant Heart of Devotion", "Reflective Scales", "Rusting Grasp", "Shape Stone", "Soft Landing", "Solid Fog", "Soothing Spring", "Speak with Plants",
"Spike Stones", "Stoneskin", "Swarming Wasp Stings", "Tortoise and the Hare", "Vital Beacon", "Wall of Fire", "Weapon Storm"};

vector<string> Primal_5th_Level = {"Acid Storm","Banishmnent", "Blackfingers Blades", "Blazing Fissure", "Blessing of Defiance", "Blinding Foam", "Blister", "Chameleon Coat",
"Cloudkill", "Cone of Cold", "Control Water", "Death Ward", "Desperate Repair", "Elemental Form", "Flammable Fumes", "Flowing Strike", "Geyser", "Glimmer of Charm",
"Grisly Growths","Healing Well", "Impaling Strike","Incendiary Fog","Lashunta's Life Bubble", "Lighting Storm", "Mantle of the Frozen Heart", "Mantle of the Magma Heart", "Mariner's Curse",
"Moon Frenzy", "Passwall", "Pillars of Sand", "Plant FOrm", "Ravening Maw", "Ritual Obstruction", "Soulshelter Vessel", "Stormburst", "Summon Giant", "Summon Healing Servitor",
"Temporary Glyph","Transmute Rock and Mud", "Tree Stride","Wall of Flesh","Wall of Ice", "Wall of Stone","Wyvern Sting"};

vector<string> Primal_6th_Level = {"Baleful Polymorph", "Blanket of Stars", "Blinding Fury", "Catch Your Name", "Chain Lightning", "Dragon Form", "Elemental Confluence",
"Field of Life","Fire Seeds", "Flame Vortex", "Flesh to Stone", "Hag's Fruit", "Halcyon Infusion", "Nature's Reprisal", "Necrotize", "Purple Worm Sting", "Rose's Thorn's",
"Scintillating Safegaurd", "Stone Tell", "Stone to Flesh", "Tangling Creepers","True Seeing"};

vector<string> Primal_7th_Level = {"Blighburn Blast", "Corrosive Body", "Cosmic  Form", "Eclipse Burst", "Energy Aegis", "Fiery Body", "Finger of Death","Frigid Fury",
"Mask of Terror", "Moonburst", "Plane Shift", "Regenerate", "Sunburst", "Unfettered Pack", "Volcanic Eruption"};

vector<string> Primal_8th_Level = {"All is One, One is All","Boil Blood", "Burning Blossoms", "Clone Companion", "Deluge", "Earthquake", "Horrid Wilting",
 "Moment of Renewal","Monstrocity Form", "Polar Ray", "Punishing Winds", "Whirlwind","Wind Walk"};

vector<string> Primal_9th_Level = {"Disjuntion", "Implosion", "Linnorm Sting", "Massacre", "Meteor Swarm", "Nature's Enmity", "One with the Land", "Shapechange",
"Storm of Vengeance", "Upheaval"};

vector<string> Primal_10th_Level ={"Cataclysm", "Dinosaur Fort", "Element Embodied","Fated Confrontation", "Indestructibility", "Nature Incarnate",
"Nullify", "Primal Herd", "Primal Phenomenon", "Remake", "Reviaval", "Summon Kaiju"};

#endif /* Primal_h */
