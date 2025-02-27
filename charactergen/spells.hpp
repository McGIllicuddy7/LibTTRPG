//
//  Arcane.h
//  Pathfinder_Character_Generator
//
//  Created by Isaac Hartin Pasco on 7/7/23.
//
#pragma once
#ifndef Arcane_h
#define Arcane_h
#pragma once
#include <vector> 
#include <string_view>
using std::vector;
using std::string_view;
inline vector<string_view> Arcane_Cantrips = {"Arcane Slash", "Ancient Dust", "Bullhorn", "Chill Touch", "Dancing Lights", "Dancing Lights", "Daze", "Detect Magic",
"Electric Arc", "Gale Blast", "Ghost Sound", "Gouging Claw", "Infectious Enthusiasm", "Invoke True Name", "Light", "Mage Hand", "Message", "Muscial Accompaniment",
"Phase Bolt","Prestidigitation","Produce Flame","Protect Companion", "Puff of Poison","Ray of Frost", "Read Aura","Scatter Scree", "Shield","Sigil","Spout","Tanglefoot",
"Telekinetic Projectile", "Time Sense", "Torturous Trauma", "Warp Step"};

inline vector<string_view> Arcane_1st_Level = {"Acidic Burst","Admonishing Ray", "Agitate", "Airburst", "Alarm","Animate Dead", "Animate Rope", "Ant Haul", "Anticpate Peril",
"Aqueous Burst", "Befuddle","Breadcrumbs","Briny Bolt","Burning Hands","Charm", "Chilling Spray", "Color Spray", "Command", "Create Water", "Deja Vu", "Draw Ire",
"Echoing Weapon", "Elysian Whimsy", "Endure", "Exchange Image", "Fashionist", "Flashy Disappearance", "Fleet Step", "Flense", "Floating Disk", "Friendfetch", "Goblin Pox",
"Gravitational Pull", "Grease", "Grim Tendrils", "Gritty Wheeze", "Gust of Wind","Helpful Steps", "Horizon Thunder Sphere", "Hydraulic Push", "Illusory Disguise",
"Illusory Object", "Illusory Item", "Invisible Item", "Item Facade", "Jump", "Kinetic Ram", "Lock", "Longstrider", "Mage Armor", "Magic Aura", "Magic Missle", "Magic Weapon",
"Mending", "Message Rune", "Mud Pit", "Necromancers Generosity", "Negate Aroma", "Noxious Vapors", "Nudge the Odds", "Overselling Flourish", "Penumbral Shroud",
"Personal Rain Cloud", "Pest Form", "Pet Cache", "Pocket Library", "Pumelling Rubble", "Quick Sort", "Ray of Enfeeblement","Restyle", "Shadenfreude", "Scorching Blast",
"Seashell of Stolen Sound", "Share Lore", "Scattering Gem", "Shocking Grasp", "Shockwave","Sleep", "Summon Animal", "Summon Construct", "Synchronize", "Synchronize Steps",
"Temporary Tool", "Tether", "Thicket of Knives", "Thoughful Gift", "True Strike", "Unseen Servant", "Ventriloquism"};

inline vector<string_view> Arcane_2nd_Level = {"Acid Arrow", "Animated Assualt", "Ash Cloud", "Befitting Attire", "Blood Duplicate", "Blood Vendetta", "Blur", "bone Spray",
"Boneshaker", "Charitable Urge", "Comprehend Language", "Confetti Cloud", "Continual Flame", "Create Food", "Dancing Shield", "Darkness","Darkvision", "Deafness",
"Dismantle", "Dispell Magic", "Elemental Zone", "Empathic Link", "Empty Pack", "Endure Elements","Enlarge","Expeditious Excavation","Extract Poison","False Life",
"Fear the Sun", "Feast of Ashes", "Final Sacrifice", "Flame Wisp", "Flaming Sphere", "Gentle Repose", "Glitterdust", "Heat Metal", "HIdeous Laughter","Humanoid Form",
"Horrifying Blood Loss","Ignite Fireworks", "Illusory CReature", "Illusory Shroud", "IMpeccable Flow", "Instant Armor", "Instant Parade", "Invisiblity", "Iron Gut", "Knock",
"Lock Item", "Loose Time's Arrow", "Lucky Number", "Magic Mouth", "Magnetic Attraction", "Magnetic Repulsion", "Mind Games", "Mirror Image", "Misdirection", "Obscuring Mist",
"Penumbral Disguise", "Persistent Servant", "Phatasmal Treasure", "Phantom Crowd", "Radiant Field", "Rapid Adaption", "Resist Energy", "Rime Slick","Scorching Ray",
"Sea surge", "See Invisibilty", "Shadow Zombie", "Shrink", "Slough Skin", "Spectral Hand", "Spider Climb", "Spys  Mark", "Sudden Bolt", "Summon Elemental", "Summoners Precaution",
"Summoners Visage", "Swallow Light", "Telekntic Maneuver", "Timely Tutor", "Touch of Idiocy", "Umbral Extraction","Umbral Mindtheft", "Vicious Jealousy","Vomit Swarm",
"Warriors Regret", "Water Breathing", "Water Walk","Web"};

inline vector<string_view>  Arcane_3rd_Level = {"Agonizing Despair", "Aqueous Orb", "Bind Undead", "Blazing Dive", "Blindess", "Bottomless Stomach", "Bracing Tendrals",
"Casters Imposition", "Clairaudience", "Cozy Cabin", "Crashing Wave", "Cup of Dust", "Curse of Lost Time", "Days Weight", "Distracting Chatter", "Dividing Trench",
"Dream Message", "Earthbind", "Elemental Absorption", "Enemtal Annihilation Wave", "Enthrall", "Excise Lexicon", "Familiars Face", "Feet to Fins","Fireball",
"Firework Blast","Gasping Marsh", "Ghostly Weapon", "Glyph of Warding", "Gravity Well", "Haste", "Hypnotic Pattern", "Impending Doom", "Invisibilty Sphere", "Lashing Rope",
"Levitate", "Lightning Bolt", "Locate", "Magical Fetters", "Magnetic Acceleration", "Meld into Stone", "Mind of Menace", "Mind Reading", "Nondetection",
"Nothing up my Sleeve", "Oneiric Mire", "Ooze Form", "Organsight", "Paralyze","Percussive Impact","Perseis's Precautions", "Phantom Prison","Pillar of Water", "Pyrotechnics",
"Rally Point", "Roaring Applause", "Rouse Skeletons", "Safe Passage", "Sea of Thought", "Secret Page", "Shadow Projectile", "Shift Blame", "Shifting Sand","Slow","Sparkleskin",
"Stinking Clowd", "Temporal Twin", "Time Jump", "Time Pocket", "Transcibe Conflict", "Unseasonable Squall", "Vampiric Touch", "Wall of Radiance", "Wall of Shadow",
"Wall of Virtue", "Wall of Water", "Wall of Wind", "Warding Aggresion", "Web of Eyes",};

inline vector<string_view>  Arcane_4th_Level = {"Aerial Form", "Aromatic Lure", "Bestial Curse", "Blink", "Call the Blood", "Chromatic Armor", "Chromatic Ray", "Clairvoyance",
"Clownish Curse", "Compel True Name", "Confusion", "Coral Eruption", "Counless Eyes", "Creation", "Daydreamers Curse", "Detect Creator", "Detect Scrying", "Dimension Door",
"Dimensional Anchor", "Discern Lies", "Draw the Lightning", "Dull Ambition", "Enervation", "Enhance Senses", "False Nature", "Favorable Review", "Fire Shield",
"Fly", "Forgotten Lines", "Gaseous Form","Globe of Invulnerablity", "Hallucinatory Terrain", "Ice Storm", "invisibility Curtain", "Magic Mailbox", "Mirrors Misfortune",
"Morass of Ages", "Necrotic Radiation", "Nighmare", "Ocular Overload", "Outcast's Curse", "Phantasmal Killer", "Private Sanctum", "Ravenous Portal",
"Rebounding Barrier", "Reflective Scales", "Replicate", "Resilient Sphere", "Rope Trick", "Sages Curse", "Sanguine Mist", "Seal Fate", "Shape Stone","Soft Landing",
"Solid Fog", "Spell Immunity", "Steal Voice", "Stoneskin", "Suggestion", "Swarming Wasp Stings", "Telepathy", "Umbral Graft", "Vampiric Maiden", "Variable Gravity", "Veil",
"Vision of Beauty", "Wall of Fire", "Weapon Storm", "Winning Streak"};

inline vector<string_view>  Arcane_5th_Level = {"Acid Storm", "Bandits Doom", "Banishment", "Belittling Boast", "Black Tentacles", "Blazing Fissure", "Blinding Foam", "Blink Charge", "Blister",
"Blood Feast", "Chromatic Wall", "Cloak of Colors", "Cloudkill", "Cone of Cold", "Control Water", "Crushing Despair", "Desperate Repair", "Drop Dead", "Elemental Form", "Etheric Shards"
, "False Vision", "Flammable Fumes", "Flowing Strike", "Forceful Hand", "Geyser", "Glimmer of Charm", "Grisly Growths", "Hallucination", "Illusory Scene", "Impaling Strike",
"Incendiary Fog", "Infectious Comedy", "Invoke Spirits", "Lashuntas Life Bubble", "Mantle of the Frozen Heart", "Mantle of the Magma Heart", "Mariner's Curse", "Mind Probe",
"Mirror Malfactors", "Passwall","Pillars of Sand","Prying Eye", "Quicken Time", "Return Beacon", "Rewinding Step", "Ritual Obstruction", "Scouring Pulse", "Secret Chest",
"Sending", "Shadow Siphon", "Shadow Walk","Stagnate Time", "Subconscious Suggestion", "Summon Dragon", "Telekninetic Haul", "Telepathic Bond", "Temporary Glyph","Tongues"
,"Transmute Rock and Mud", "Wall of Ice", "Wall of Stone", "Wyvern Sting"};

inline vector<string_view>  Arcane_6th_Level = {"Aura of the Unremarkable", "Awaken Entropy", "Baleful Polymorph", "Bound in Death", "Cast into Time", "Catch your Name", "Chain Lightning",
"Chromatic Image", "Collective Transposition", "Daemon Form", "Demon Form", "Devil Form", "Disintegrate", "Dominate", "Dragon Form", "Elemental Confluence", "Feeblemind",
"Flame Vortex", "Flesh to Stone", "Halcyon Infusion", "Mislead", "Necrotize", "Phatasmal Calamity", "Poltergeists Fury", "Purple Worm Sting", "Ravenous Darkness",
"Repulsion", "Scrying", "Spellwrack", "Teleport", "Temporal Ward", "True Seeing","Unexpected Transposition", "Vampiric Exsanguination", "Virbant Patter", "Wall of Force",
"Word of Revision", "Zero Gravity"};

inline vector<string_view>  Arcane_7th_Level = {"Blightburn Blast", "Contingency", "Control Sand", "Corrosive Body","Dimensional Lock","Duplicate Foe","Eclipse Burst","Energy Aegis",
"Entrancing Eyes","Fiery Body","Force Cage","Frigid Flurry","Inexhaustible Cynicism", "Long Sting","Magnificent Mansion","Mask of Terror","Momentary Recovery","Plane Shift",
"Power Word Blind","Prismatic Armor","Prismatic Spray","Project Image","Return to Essence", "Reverse Gravity","Shadow Raid","Spell Turning","Telekinetic Bombardment",
"Tempest of Shades","Time Beacon","True Target", "Warp Mind"};

inline vector<string_view>  Arcane_8th_Level = {"All is One, One is All", "Antimagic Field", "Boil Blood", "Burning Blossoms", "Deluge", "Disappearance", "Discern Location", "Dream Council",
"Earthquake", "Falling Sky", "Horrid Wilting", "Maze", "Mind Blank", "Monstrosity Form", "Polar Ray", "Power Word Stun", "Prismatic Wall", "Prying Survey", "Scintillating Pattern",
"Summon Archmage", "Summon Irii", "Uncontroolable Dance", "Undermine Reality", "Unrelenting Observation"};

inline vector<string_view>  Arcane_9th_Level = {"Astral Labrynth", "Bilocation", "Disjunction", "Divinity Leech","Foresight","Implosion", "Linnorm Sting", "Massacre", "Meteor Swarm",
"Power word Kill", "Prismatic Shield", "Proliferating Eyes","Resplendent Mansion", "Shapechange", "Summon Ancient Fleshforged", "Summon Draconic Legion", "Telepathic Demand",
"Unspeakable Shadow", "Upheaval","Weird"};

inline vector<string_view>  Arcane_10th_Level = {"Cataclysm", "Fated Confrontation", "Gate", "Indestructibility","Nullify", "Remake","Shadow Army","Time Stop","Wish"};

inline vector<string_view> Divine_Cantrips = {"Ancient Dust", "Approximate", "Bullhorn", "Chill Touch", "Daze", "Detect Magic", "Disrupt Undead", "Divine Lance", "Forbidding Ward",
    "Guidance", "Haunting Hymn", "Inside Ropes", "Invoke True Name", "Know Direction", "Light", "Message", "Prestidigitation", "Protect Companion", "Read Aura", "Read the Air",
    "Shield", "Sigil", "Stabilize", "Summon Instrument", "Torturous Tramua", "Wash Your Luck"};
    
    inline vector<string_view> Divine_1st_Level = {"Admonishing Ray", "Air Bubble", "Alarm", "Animate Dead", "Bane", "Bless", "Breadcrumbs", "Celestial Accord", "Command",
    "Concordant Choir", "Create Water", "Detect Alignment", "Detect Poison", "Disrupting Weapons", "Echoing Weapon", "Elysian Whimsy", "Fear", "Forced Mercy",
    "Harm", "heal", "Helpful Steps", "Lock", "Magic Stone", "Magic Weapon", "Mending", "Necromancer's Generosity", "Nudge the Odds", "Pet Cache", "Protection","Purify Food and Drink",
    "Purifying Icicle", "Putrefy Food and Drink", "Quick Sort","Ray of Enfeeblement","Restyle","Sanctuary","Schadenfreude","Spirit Link","Summon Lesser Servitor",
    "Synchronize","Thoughtful Gift", "Ventriloquism"};
    
    inline vector<string_view> Divine_2nd_Level = {"Advanced Scurvy","Augury", "Blazing Blade", "Blood Vendetta", "Bone Spray", "Boneshaker", "Bralani Referendum",
    "Brand The Impenitent", "Calm Emotions", "Charitable Urge", "Clawsong", "Comprehend Languages", "Continual Flame", "Create Food", "Dancing Shield",
    "Darkness", "Darkvision", "Deafness", "Death Knell", "Dispell Magic", "Endure Elements", "Enhance Vicutals", "Faerie Fire", "Fear the Sun", "Final Sacrifice", "Gentle Repose",
    "Ghoulish Cravings", "Grave Impressions", "Guiding Star", "Horrifying Blood Loss", "Imp Sting", "Impeccable Flow", "Inner Radiance Torrent", "Instant Armor", "Lucky Number",
    "Mimic Undead", "Radiant Field", "Reaper's Lantern", "Remove Fear", "Remove Paralysis", "Resist Energy", "Restoration", "Restore Senses", "See Invisibility", "Shadow Zombie"
    ,"Shield Other", "Silence", "Sound Burst", "Spirit Sense", "Spiritual Weapon", "Statue", "Sudden Blight", "Summoners Precaution", "Summoners Visage",
    "Swallow Light", "Undetectable Alignment", "Vicious Jealousy", "Warriors Regret", "Water Breathing", "Water Walk"};
    
    inline vector<string_view> Divine_3rd_Level = {"Agonizing Despair", "Behold the Weave", "Bind Undead", "Blindness","Casters Imposition", "Chilling Darkness","Circle of Protection",
    "Claim Curse", "Consecrate Flesh", "Crisis of Faith", "Dream Message", "Familiars Face", "Focusing Hum", "Glyph of Warding", "Heroism", "Impending Doom", "Infectious Ennui",
    "Life Connection", "Life Pact", "Locate", "Martyr's Intervention", "Mind of Menace", "Moonlight Ray", "Neutralize Poison", "Organsight", "Percussive Impact",
    "Positive Attunement", "Remove Disease", "Roaring Applause", "Rouse Skeletons", "Safe Passage", "Sanctified Ground", "Searing Light", "Show the Way",
    "Sign of Conviction", "Soothing Blossoms","Sparkleskin", "Vampiric Touch","Wall of Virtue", "Wanderers Guide", "Warding Aggresion", "Web of Eyes",
    "Whirling Scarves", "Zone of true"};
    
    inline vector<string_view> Divine_4th_Level = {"Air Walk", "Anathematic Reprisal", "Bloodspray Curse", "Cloak of Light", "Compel True Name", "Dawnflowers Light", "Detect Creator",
    "Dimensional Anchor", "Dirge of Remembrance", "Discern Lies", "Divine Wrath", "Dull Ambition", "Enervation", "Enhance Sense", "Forgotten Lines","Freedom of Movement",
    "Ghostly Tragedy", "Girzanie's March", "Globe of Invulnerability", "Holy Cascade", "Implement of Destruction", "Internal Insurrection", "Magic Mailbox",
    "Movanic Glimmer", "Nectrotic Radiation", "Outcasts Curse", "Painful Vibrations", "Pernicious Poltergeist", "Phantasmal Protagonist", "Radiant Beam",
    "Radiant Heart of Devotion", "Read Omens", "Remove Curse","Sqanguine Mist", "Seal Fate", "Soothing Spring", "Spell Immunity", "Spiritual Anamnesis",
    "Spiritual Attunement", "Talking Corse", "Vampiric Maiden", "Vital Beacon"};
    
    inline vector<string_view> Divine_5th_Level = {"Abyssal Plane", "Bandits Doom", "Banishment", "Belittling Boast", "Blackfingers Blades", "Blessing of Defiance", "Blink Charge",
    "Blood Feast", "Death Ward", "Drop Dead", "Flame Strike", "Healing Well", "Inevitable Disaster", "Invoke Spirits", "Lashunta's Life Bubble", "Mirecloak",
    "Mirror Malefactors", "Prying Eye", "Rallying Banner", "Ravening Maw", "Rewinding Step", "Rip the Spirit", "Ritual Obstruction", "Scouring Pulse", "Shadow Blast",
    "Soulshelter Vessel", "Spiritual Guardian", "Spiritual Torrent", "Summon Anarch", "Summon Axiom", "Summon Celestial", "Summon Fiend", "Summon Healing Servitor",
    "Temporary Glyph", "Tongues", "Wall of Flesh"};
    
    inline vector<string_view> Divine_6th_Level = {"Awaken Entropy", "Blade Barrier", "Blinding Fury", "Bound in Death", "Catch Your Name", "Daemon Form", "Demon Form", "Devil Form",
    "Field of Life","Mantle of Heaven's Slopes","Necrotize", "Raise Dead", "Ravenous Darkness", "Repulsion", "Righteous Might", "Scintillating Safeguard", "Spellwrack",
    "Spirit Blast", "Stone Tell", "Stone to Flesh", "Suffocate", "Suspended Retribution", "Temporal Ward", "True Seeing", "Vampiric Exsanguination", "Zealous Conviction"};
    
    inline vector<string_view> Divine_7th_Level = {"Angel Form", "Cosmic Form", "Deity's Strike", "Dimensional Lock", "Divine Decree", "Divine Vessel", "Eclipse Burst", "Energy Aegis", "Etheral Jaunt",
    "Finger of Death", "Inexhastible Cynicism", "Moonburst", "Plane Shift", "Regenerate","Return to Essence", "Sunburst","Tempese of Shades"};
    
    inline vector<string_view> Divine_8th_Level = {"Antimagic Field", "Canticle of Everlasting", "Devour Life", "Discern Location", "Divine Armageddon", "Divine Aura", "Divine Inspiration",
    "Moment of Renewal", "Spiritual Epidemic", "Summon Deific Herald"};
    
    inline vector<string_view> Divine_9th_Level = {"Astral Labrynth", "Bind Soul", "Crusade", "Foresight", "Massacre", "Overwhelming Presence", "Proliferating Eyes", "Telepathic Demand",
    "Undertaker", "Voracoius Gestalt", "Wall of the Banshee", "Weapon of Judgment"};
    
    inline vector<string_view> Divine_10th_Level = {"Avatar", "Fated Confrontation", "Gate", "Indestructability", "Miracle", "Nullify", "Remake", "Revival"};
    inline vector<string_view>  Occult_Cantrips = {"Approximate", "Bullhorn", "Chill Touch", "Dancing Lights", "Daze", "Detect Magic", "Forbidding Ward", "Ghost Sound", "Guidance",
        "Haunting Hymn", "Infectious Enthusiasm", "Inside Ropes", "Invoke True Name", "Join Pasts", "Know Direction", "Light", "Mage Hand", "Message", "Musical Accompaniment",
        "Phase Bolt", "Prestidigitation","Protect Companion", "Read Aura", "Read the Air", "Shield", "Sigil", "Summon Instrument", "Tame", "Telekinetic Projectile", "Time Sense",
        "Warp Step", "Wash Your Luck"};
        
    inline vector<string_view>  Occult_1st_Level = {"Agitate", "Alarm", "Animate Dead", "Anticipate Peril", "Aqueous Blast", "Bane", "Biting Words", "Bless", "Breadcrumns", "Celestial Accord",
        "Charm", "Color Spray", "Command", "Concordant Choir", "Deja Vu", "Detect Alignment", "Draw Ire", "Echoing Weapon", "Endure", "Exchange Image", "Fashionista",
        "Fear", "Flashy Disappearance", "Floating Disk", "Forced Mercy", "Friendfetch", "Gravitational Pull", "Grim Tendrils", "Helpful Steps", "Ill Omen", "Illsury Disguise",
        "Illusory Object", "Imprint Message", "Inkshot", "Invisible Item", "Item Facade", "Kinetic Ram", "Liberating Command", "Lock", "Lose the Path", "Mage Armor", "Magic Aura",
        "Magic Missile", "Magic Weapon", "Mending", "Message Rune", "Mindlink", "Nudge the Odds", "Object Reading", "Overselling Flourish", "Penumbral Shroud", "Pet Cache",
        "Phantom Pain", "Pocket Library", "Protection", "Quick Sort", "Ray of Enfeeblement", "Restyle", "Sanctuary", "Shadenfreude", "Scorching Blast", "Seashell of Stolen Sound",
        "Share Lore", "Sleep", "Soothe", "Spirit Link", "Summon Fey", "Synchronize", "Synchronize Steps", "Thicket of Knives", "Thoughtful Gift", "True Strike", "Unseen Servant",
        "Ventriloquism"};
        
inline vector<string_view> Occult_2nd_Level = {"Animated Assault", "Animus Mine","Augury","Befitting Attire", "Blistering Invective", "Blood Duplicate", "Blood Vendetta", "Blur",
        "Calm Emotions", "Charitable Urge", "Comprehend Langagues", "Confetti Cloud", "Continual Flame", "Cutting Insult", "Dancing Shield", "Darkness", "Darkvision",
        "Deafness", "Death Knell", "Dispel Magic", "Empathic Link", "Empty Pack", "Faerie Fire", "False Life", "Fear the Sun", "Feast of Ashes", "Final Sacrifice",
        "Gentle Repose", "Ghoulish Cravings", "Grave Impressions", "Hideous Laughter", "Horrifying Blood Loss", "Humanoid Form", "Illusory Creature", "Illusory Shroud",
        "Imp Sting", "Impart Empathy", "Inner Radiance Torrent", "Instant Armor", "Instant Parade", "Invisibility", "Knock", "Loose Time's Arrow", "Lucky Number", "Magic Mouth",
        "Mimic Undead", "Mind Games", "Mirror Image", "Misdirection", "Pack Attack", "Paranoia", "Penumbral Darkness", "Persistent Servant", "Phatasmal Treasure",
        "Phantom Crowd", "Phantom Steed", "Radiant Field", "Reaper's Lantern", "Remove Fear", "Remove Paralysis", "Resist Energy", "Restoration", "Restore Senses","See Invisibility",
        "Shadow Zombie", "Shatter", "Silence", "Sonata Span", "Sound Burst", "Spectral Hand","Spirit Sense", "Spiritual Weapon", "Spy's Mark", "Status","Summoner's Precaution",
        "Summoner's Visage", "Swallow Light", "Teeth to Terror", "Telekinetic Maneuver", "Thundering Dominance", "Timely Tutor", "Touch of Idiocy", "Umbral Extraction",
        "Umbral Mindtheft", "Undetectable Alignment", "Vicious Jealousy", "Vomit Swarm","Warriors Regret", "Worms Repast"};
        
inline vector<string_view> Occult_3rd_Level = {"Agonizing Despair","Behold the Weave", "Bind Undead", "Blindness", "Bottomless Stomach", "Bracing Tendrils", "Caster's Imposition",
        "Circle of Protection", "Claim Curse", "Clairaudience", "Cozy Cabin","Cup of Dust", "Curse of Lost Time", "Cyclone Rondo", "Days Wieght", "Distracting Chatter", "Dream Message",
        "Enthrall", "Excise Lexicon", "Familiar's Face", "Far Sight", "Focusing Hum", "Ghostly Weapon", "Glyph of Warding", "Gravity Well", "Haste", "Heroism", "Hypercognition",
        "Hypnotic Pattern", "Impending Doom", "Infectious Ennui", "Lashing Rope", "Levitate", "Life Pact", "Locate", "Magical Fetters", "Martyr's Intervention", "Mind of Menace",
        "Mind Reading", "Moth's Supper", "Nondetection", "Nothing Up My Sleeve", "Oneiric Mire", "Ooze Form", "Organsight", "painted Scout", "Paralyze", "Percussive Impact",
        "Perseis's Precautions", "Phantom Prison", "Pyrotechnics", "Rally Point", "Roaring Applause", "Rouse Skeletons", "Sculpt Sound", "Sea of Thought", "Secret Page",
        "Shadow Projectile", "Shadow Spy","Shift Blame", "Slow", "Sparkleskin", "Sudden Recollection", "Temporal Twin", "Threefold Aspect", "Time Jump", "Time Pocket", "Transcibe Conflict",
        "Vampiric Touch", "Wall of Shadow","Wanderer's Guide", "Web of Eyes","Whirling Scarves","Zone of Truth"};
        
inline vector<string_view> Occult_4th_Level = {"Aromatic Lure", "Bestial Curse", "Blink", "Bloodspray Curse", "Bursting Bloom", "Call the Blood", "Chroma Leech", "Chromatic Armor",
        "Chromatic Ray", "Clairvoyance", "Clownish Curse", "Compel True Name", "Confusion", "Countless Eyese", "Dawnflower's Light", "Daydreamer's Curse", "Detect Creator",
        "Detect Scrying", "Dimension Door", "Dimensional Anchor", "Dirge of Remembrance", "Discern Lies", "Dull Ambition", "Enervation","Enhance Senses", "False Nature",
        "Favorable Review", "Fey Form", "Fly", "Forgotten Lines", "Gaseous Form", "Ghostly Tragedy", "Girzanje's March", "Glibness", "Globe of Invulernability",
        "Hallucinatory Terrain", "Implement of Destruction", "Infectious Melody", "Internal Insurrection", "Invisibility Curtain", "Magic Mailbox", "Mirrors Misfortune",
        "Modify Memory", "Morass of Ages", "Necrotic Radiation", "Nightmare", "Ocular Overload", "Outcast's Curse", "Painful Vibrations", "Pernicious Poltergeist",
        "Phantasmal Killer", "Phatasmal Protagonist", "Private Sanctum", "Procyal Philosophy", "Ravenous Portal","Read Omens", "Rebounding Barrier", "Remove Curse", "Replicate",
        "Resilient Sphere", "Rope Trick", "Sage's Curse", "Sanguine Mist", "Seal Fate", "Soft Landing","Spell Immunity", "Spiritual Anamnesis", "Spiritual Attunement",
        "Suggestion", "Talking Corpse", "Telepathy", "Tortoise and the Hare", "Umbral Graft", "Vampiric Maiden", "Variable Gravity", "Veil","Vision of Beauty", "Winning Streak"};
        
        inline vector<string_view> Occult_5th_Level = {"Abberant Form", "Abyssal Plague", "Bandit's Doom", "Banishment", "Belittling Boast", "Black Tentacles", "Blink Eyese", "Blinding Foam",
        "Blink Charge", "Blister", "Blood Feast", "Chromatic Wall", "Cloak of Colors", "Crushing Despair", "Death Ward", "Dreaming Potential", "Ectoplasmic Expulsion",
        "Etheric Shards", "False Vision", "Forceful Hand", "Glimmer of Charm", "Hallucination", "Illusory Scene", "Inevitable Disaster", "Infectious Comedy", "Invoke Spirits",
        "Mariner's Curse", "Mind Probe", "Mirecloak","Mirror Malefactors", "Portrait of the Artist", "Prying Eye", "Quicken Time","Rallying Banner", "Ravening Maw",
        "Repelling Pulse", "Return Beacon", "Rewinding Step", "Rip the Spirit", "Ritual Obstruction", "Scouring Pulse", "Secret Chest", "Sending", "Shadow Blast",
        "Shadow Siphon", "Soulshelter Vessel", "Stagnate Time", "Strange Geometry", "Subconscious Suggestion", "Summon Entity", "Synaptic Pulse", "Synesthesia","Telekinetic Haul",
        "Telepathic Bond", "Temporary Glyph", "Tongues", "Wall of Flesh"};
        
        inline vector<string_view> Occult_6th_Level = {"Aura of the Unremarkable", "Awaken Entropy", "Blanket of Stars", "Blinding Fury","Bound in Death", "Cast into Time",
        "Catch Your Name", "Chromatic Image", "Collective Transposition", "Dominate", "Feeblemind", "Hag's Fruit", "Lure Dream","Mislead", "Phatasmal Calamity", "Poltergeist's Fury",
        "Ravenous Darkness","Repulsion","Scintillating Safegaurd","Scrying","Spellwrack","Spirit Blast","Suspended Retribution","Teleport","Temporal Ward","True Seeing",
        "Unexpected Transposition", "Vampiric Exsanguination", "Vibrant Pattern", "Wall of Force","Word of Revision", "Zealous Conviction", "Zero Gravity"};
        
        inline vector<string_view> Occult_7th_Level = {"Blightburn Blast", "Curse of the Spirit Orchestra","Dimensional Lock", "Duplicate Foe", "Energy Aegis", "Ethereal Jaunt", "Force Cage",
        "Inexhastible Cynicism", "Leng Sting", "Mask of Terror", "Magnificent Mansion", "Maze of Locked Doors", "Momentary Recovery", "Plane Shift", "Posession", "Prismatic Armor",
        "Prismatic Spray", "Project Image", "Retrocognition", "Return to Essence", "Reverse Gravity", "Shadow Raid", "Telekinetic Bombardment", "Tempest of Shades", "Time Beacon",
        "True Target", "Visions of Danger", "Warp Mind"};
        
        inline vector<string_view> Occult_8th_Level = {"Antimagic Field","Canticle of Everlasting Grief","Devour Life","Disaperrance","Discern Location","Dream Council","Falling Sky","Hypnopompic Terrors",
        "Maze","Mind Blank","Prismatic Wall","Prying Survey", "Scintillating Pattern","Spirit Song","Spiritual Epidemic","Summon Irii","Uncontrollable Dance","Undermine Reality",
        "Unrelenting Observation"};
        
        inline vector<string_view> Occult_9th_Level = {"Astral Labyrinth", "Bilocation","Bind Soul", "Divinity Leech", "Foresight","Overwhelming Presence", "Prismatic Shield","Prismatic Sphere",
        "Proliferating Eyes","Resplending Mansion","Summon Ancient Fleshforged","Telepathic Demand","Undertaker","Unfathomable Song","Unspeakable Shadow", "Voracious Gestalt", "Wail of the Banshee",
        "Wierd"};
        
        inline vector<string_view> Occult_10th_Level = {"Alter Reality","Fabricated Truth","Fated Confrontation","Gate","Indestructibility","Nullify","Remake","Shadow Army","Time Stop"};
        inline vector<string_view> Primal_Cantrips = {"Acid Splash", "Approximate", "Dancing Lights", "Detect Magic", "Disrupt Undead", "Electric Arc", "Gale Blast", "Gouging Claw", "Guidance",
            "Healing Plaster", "Inside Ropes", "Invoke True Name", "Know Direction", "Light", "Prestidigitation", "Produce Flame", "Protect Companion", "Puff of Poison", "Ray of Frost",
            "Read Aura", "Scatter Scree", "Sigil", "Spout", "Stabilize", "Tame", "Tanglefoot"};
            
            inline vector<string_view> Primal_1st_Level = {"Acidic Burst", "Air Bubble", "Airburst", "Alarm", "Animal Allies", "Ant Haul","Aqueous Blast", "Breadcrumbs", "Briny Bolt",
            "Buffeting Winds", "Burning Hands","Charm", "Chilling Spray", "Create Water", "Detect Poison", "Elysian Whimsy", "Fear",  "Feather Fall","Fleet Step", "Goblin Pox",
            "Grease",  "Gritty Wheeze", "Gust of Wind", "Heal", "Helpful Steps", "Horizon Thunder Sphere","Hydraulic Push","Inkshot", "Jump", "Juvenile Companion", "Longstrider",
            "Lose the Path", "Magic Fang", "Magic Stone", "Mending", "Mud Pit", "Negate Aroma", "Nettleskin", "Noxious Vapors", "Pass Without Trace", "Personal Rain Cloud", "Pest Form",
            "Pet Cache", "Protector Tree", "Pummeling Rubble","Purify Food and Drink", "Purifiying Icicle", "Quick Sort", "Restyle", "Scorching Blast", "Scouring Sand", "Seashell of Stolen Sound",
            "Shattering Gem", "Shillelagh", "Shocking Grasp", "Shockwave", "Snowball", "Spider Sting","Summon Animal", "Summon Fey", "Summon Plant or Fungus", "Swampcall","Synchronize",
            "Tether", "Ventriloquism", "Verdant Sprout","Verminous Lure"};
            
            inline vector<string_view>  Primal_2nd_Level = {"Acid Arrow", "Advanced Scurvy", "Animal Form", "Animal Messenger", "Ash Cloud", "Barkskin", "Blazing Blade", "Bone Spray" "Boneshaker",
            "Bralani Referendom", "Breath of Drought", "Clawsong", "Continual Flame", "Create Food", "Dancing Shield", "Darkness", "Darkvision", "Deafness", "Dismantle", "Dispel Magic",
            "Elemental Zone", "Endure Elements", "Enhance Victuals", "Enlarge", "Entangle", "Erase Trail", "Expeditious Excavation", "Extract Poison", "Faerie Fire","Fear the Sun",
            "Feast of Ashes", "Feral Shades", "Final Sacrifice", "Flame Wisp","Flaming Sphere", "Fungal Hyphae", "Fungal Infestation", "Gentle Repose", "Glitterdust", "Guiding Star",
            "Heat Metal", "Humanoid Form", "Ignite Fireworks","Impart Empathy", "Instant Armor", "Iron Gut", "Lock Item", "Loose Time's Arrow","Magnetic Attraction", "Magnetic Repulsion",
            "Obscuring Mist", "Pack Attack", "Phantom Steed", "Quench", "Radiant Field", "Rapid Adaption", "Reaper's Lantern", "Remove Fear", "Remove Paralysis", "Resist Energy", "Restoration",
            "Restore Senses", "Rime Slick",  "Scorching Ray", "Sea Surge", "Shape Wood", "Shatter", "Shrink", "Slough Skin", "Speak with Animals","Spider Climb", "Status", "Sudden Blight",
            "Sudden Bolt", "Summon Elemental", "Summoner's Precaution", "Summoner's Visage", "Thundering Dominance", "Tree Shape", "Vomit Swarm","Water Breathing", "Water Walk",
            "Web", "Worm's Repast"};
            
            inline vector<string_view> Primal_3rd_Level = {"Animal Vision", "Aquesous Orb", "Blazing Dive", "Blindness", "Bottomless Stomach", "Caster's Imposition", "Crashing Wave",
            "Cup of Dust", "Curse of Lost time", "Cyclone Rondo", "Day's Weight", "Dividing Trench", "Earthbind", "Elemental Absorption", "Elemental Anhiliation Wave", "Envenom Companion",
            "Familiar's Face", "Far Sight", "Feet to Fins", "FireBall", "Gasping Marsh", "Glyph of Warding", "Haste", "Insect Form", "LIfe Connection", "Life Pact", "Lightning Bolt",
            "Mad Monkeys", "Magnetic Acceleration", "Martyr's Intervetion", "Meld into Stone", "Mind of Menace", "Moonlight Ray", "Moth's Supper", "Neutralize Poison","Nondetection",
            "Oneiric Mire", "Organsight", "Painted Scout", "Pillar of Water", "Positive Attunment", "Remove Disease", "Safe Passage", "Searing Light", "Shadow Spy", "Shifting Sand",
            "Show the Way", "Slow", "Soothing Blossoms", "Stinking Cloud","Threefold Aspect", "Useasonable Squall", "Wall of Radiance", "Wall of Thorns", "Wall of Water", "Wall of Wind",
            "Warding Agression", "Web of Eyes"};
            
            inline vector<string_view> Primal_4th_Level = { "Aerial Form", "Air Walk", "Bestial Curse", "Bloodspray Curse", "Bursting Bloom", "Call the Blood", "Cloak of Light","Compel True Name",
            "Coral Eruption", "Countless Eyes", "Creation", "Dinosaur Form", "Draw the Lightning", "Elemental Gift", "Elephant Form", "Enhance Senses", "Fey FOrm", "Fire Shield", "Fly",
            "Freedom of Movement", "Gaseous Form", "Hallucinatory Terrain", "Hydralic Torrent", "Ice Storm", "Movanic Glimmer", "Murderous Vine", "Ocular Overload", "Petal Storm",
            "Radiant Beam", "Radiant Heart of Devotion", "Reflective Scales", "Rusting Grasp", "Shape Stone", "Soft Landing", "Solid Fog", "Soothing Spring", "Speak with Plants",
            "Spike Stones", "Stoneskin", "Swarming Wasp Stings", "Tortoise and the Hare", "Vital Beacon", "Wall of Fire", "Weapon Storm"};
            
            inline vector<string_view> Primal_5th_Level = {"Acid Storm","Banishmnent", "Blackfingers Blades", "Blazing Fissure", "Blessing of Defiance", "Blinding Foam", "Blister", "Chameleon Coat",
            "Cloudkill", "Cone of Cold", "Control Water", "Death Ward", "Desperate Repair", "Elemental Form", "Flammable Fumes", "Flowing Strike", "Geyser", "Glimmer of Charm",
            "Grisly Growths","Healing Well", "Impaling Strike","Incendiary Fog","Lashunta's Life Bubble", "Lighting Storm", "Mantle of the Frozen Heart", "Mantle of the Magma Heart", "Mariner's Curse",
            "Moon Frenzy", "Passwall", "Pillars of Sand", "Plant FOrm", "Ravening Maw", "Ritual Obstruction", "Soulshelter Vessel", "Stormburst", "Summon Giant", "Summon Healing Servitor",
            "Temporary Glyph","Transmute Rock and Mud", "Tree Stride","Wall of Flesh","Wall of Ice", "Wall of Stone","Wyvern Sting"};
            
            inline vector<string_view> Primal_6th_Level = {"Baleful Polymorph", "Blanket of Stars", "Blinding Fury", "Catch Your Name", "Chain Lightning", "Dragon Form", "Elemental Confluence",
            "Field of Life","Fire Seeds", "Flame Vortex", "Flesh to Stone", "Hag's Fruit", "Halcyon Infusion", "Nature's Reprisal", "Necrotize", "Purple Worm Sting", "Rose's Thorn's",
            "Scintillating Safegaurd", "Stone Tell", "Stone to Flesh", "Tangling Creepers","True Seeing"};
            
            inline vector<string_view> Primal_7th_Level = {"Blighburn Blast", "Corrosive Body", "Cosmic  Form", "Eclipse Burst", "Energy Aegis", "Fiery Body", "Finger of Death","Frigid Fury",
            "Mask of Terror", "Moonburst", "Plane Shift", "Regenerate", "Sunburst", "Unfettered Pack", "Volcanic Eruption"};
            
            inline vector<string_view> Primal_8th_Level = {"All is One, One is All","Boil Blood", "Burning Blossoms", "Clone Companion", "Deluge", "Earthquake", "Horrid Wilting",
             "Moment of Renewal","Monstrocity Form", "Polar Ray", "Punishing Winds", "Whirlwind","Wind Walk"};
            
            inline vector<string_view> Primal_9th_Level = {"Disjuntion", "Implosion", "Linnorm Sting", "Massacre", "Meteor Swarm", "Nature's Enmity", "One with the Land", "Shapechange",
            "Storm of Vengeance", "Upheaval"};
            
            inline vector<string_view> Primal_10th_Level ={"Cataclysm", "Dinosaur Fort", "Element Embodied","Fated Confrontation", "Indestructibility", "Nature Incarnate",
            "Nullify", "Primal Herd", "Primal Phenomenon", "Remake", "Reviaval", "Summon Kaiju"};
            
#endif /* Arcane_h */
