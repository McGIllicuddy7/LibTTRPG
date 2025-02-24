//
//  Occult.h
//  Pathfinder_Character_Generator
//
//  Created by Isaac Hartin Pasco on 7/7/23.
//

#ifndef Occult_h
#define Occult_h

#pragma once
vector<string>  Occult_Cantrips = {"Approximate", "Bullhorn", "Chill Touch", "Dancing Lights", "Daze", "Detect Magic", "Forbidding Ward", "Ghost Sound", "Guidance",
"Haunting Hymn", "Infectious Enthusiasm", "Inside Ropes", "Invoke True Name", "Join Pasts", "Know Direction", "Light", "Mage Hand", "Message", "Musical Accompaniment",
"Phase Bolt", "Prestidigitation","Protect Companion", "Read Aura", "Read the Air", "Shield", "Sigil", "Summon Instrument", "Tame", "Telekinetic Projectile", "Time Sense",
"Warp Step", "Wash Your Luck"};

vector<string>  Occult_1st_Level = {"Agitate", "Alarm", "Animate Dead", "Anticipate Peril", "Aqueous Blast", "Bane", "Biting Words", "Bless", "Breadcrumns", "Celestial Accord",
"Charm", "Color Spray", "Command", "Concordant Choir", "Deja Vu", "Detect Alignment", "Draw Ire", "Echoing Weapon", "Endure", "Exchange Image", "Fashionista",
"Fear", "Flashy Disappearance", "Floating Disk", "Forced Mercy", "Friendfetch", "Gravitational Pull", "Grim Tendrils", "Helpful Steps", "Ill Omen", "Illsury Disguise",
"Illusory Object", "Imprint Message", "Inkshot", "Invisible Item", "Item Facade", "Kinetic Ram", "Liberating Command", "Lock", "Lose the Path", "Mage Armor", "Magic Aura",
"Magic Missile", "Magic Weapon", "Mending", "Message Rune", "Mindlink", "Nudge the Odds", "Object Reading", "Overselling Flourish", "Penumbral Shroud", "Pet Cache",
"Phantom Pain", "Pocket Library", "Protection", "Quick Sort", "Ray of Enfeeblement", "Restyle", "Sanctuary", "Shadenfreude", "Scorching Blast", "Seashell of Stolen Sound",
"Share Lore", "Sleep", "Soothe", "Spirit Link", "Summon Fey", "Synchronize", "Synchronize Steps", "Thicket of Knives", "Thoughtful Gift", "True Strike", "Unseen Servant",
"Ventriloquism"};

vector<string> Occult_2nd_Level = {"Animated Assault", "Animus Mine","Augury","Befitting Attire", "Blistering Invective", "Blood Duplicate", "Blood Vendetta", "Blur",
"Calm Emotions", "Charitable Urge", "Comprehend Langagues", "Confetti Cloud", "Continual Flame", "Cutting Insult", "Dancing Shield", "Darkness", "Darkvision",
"Deafness", "Death Knell", "Dispel Magic", "Empathic Link", "Empty Pack", "Faerie Fire", "False Life", "Fear the Sun", "Feast of Ashes", "Final Sacrifice",
"Gentle Repose", "Ghoulish Cravings", "Grave Impressions", "Hideous Laughter", "Horrifying Blood Loss", "Humanoid Form", "Illusory Creature", "Illusory Shroud",
"Imp Sting", "Impart Empathy", "Inner Radiance Torrent", "Instant Armor", "Instant Parade", "Invisibility", "Knock", "Loose Time's Arrow", "Lucky Number", "Magic Mouth",
"Mimic Undead", "Mind Games", "Mirror Image", "Misdirection", "Pack Attack", "Paranoia", "Penumbral Darkness", "Persistent Servant", "Phatasmal Treasure",
"Phantom Crowd", "Phantom Steed", "Radiant Field", "Reaper's Lantern", "Remove Fear", "Remove Paralysis", "Resist Energy", "Restoration", "Restore Senses","See Invisibility",
"Shadow Zombie", "Shatter", "Silence", "Sonata Span", "Sound Burst", "Spectral Hand","Spirit Sense", "Spiritual Weapon", "Spy's Mark", "Status","Summoner's Precaution",
"Summoner's Visage", "Swallow Light", "Teeth to Terror", "Telekinetic Maneuver", "Thundering Dominance", "Timely Tutor", "Touch of Idiocy", "Umbral Extraction",
"Umbral Mindtheft", "Undetectable Alignment", "Vicious Jealousy", "Vomit Swarm","Warriors Regret", "Worms Repast"};

vector<string> Occult_3rd_Level = {"Agonizing Despair","Behold the Weave", "Bind Undead", "Blindness", "Bottomless Stomach", "Bracing Tendrils", "Caster's Imposition",
"Circle of Protection", "Claim Curse", "Clairaudience", "Cozy Cabin","Cup of Dust", "Curse of Lost Time", "Cyclone Rondo", "Days Wieght", "Distracting Chatter", "Dream Message",
"Enthrall", "Excise Lexicon", "Familiar's Face", "Far Sight", "Focusing Hum", "Ghostly Weapon", "Glyph of Warding", "Gravity Well", "Haste", "Heroism", "Hypercognition",
"Hypnotic Pattern", "Impending Doom", "Infectious Ennui", "Lashing Rope", "Levitate", "Life Pact", "Locate", "Magical Fetters", "Martyr's Intervention", "Mind of Menace",
"Mind Reading", "Moth's Supper", "Nondetection", "Nothing Up My Sleeve", "Oneiric Mire", "Ooze Form", "Organsight", "painted Scout", "Paralyze", "Percussive Impact",
"Perseis's Precautions", "Phantom Prison", "Pyrotechnics", "Rally Point", "Roaring Applause", "Rouse Skeletons", "Sculpt Sound", "Sea of Thought", "Secret Page",
"Shadow Projectile", "Shadow Spy","Shift Blame", "Slow", "Sparkleskin", "Sudden Recollection", "Temporal Twin", "Threefold Aspect", "Time Jump", "Time Pocket", "Transcibe Conflict",
"Vampiric Touch", "Wall of Shadow","Wanderer's Guide", "Web of Eyes","Whirling Scarves","Zone of Truth"};

vector<string> Occult_4th_Level = {"Aromatic Lure", "Bestial Curse", "Blink", "Bloodspray Curse", "Bursting Bloom", "Call the Blood", "Chroma Leech", "Chromatic Armor",
"Chromatic Ray", "Clairvoyance", "Clownish Curse", "Compel True Name", "Confusion", "Countless Eyese", "Dawnflower's Light", "Daydreamer's Curse", "Detect Creator",
"Detect Scrying", "Dimension Door", "Dimensional Anchor", "Dirge of Remembrance", "Discern Lies", "Dull Ambition", "Enervation","Enhance Senses", "False Nature",
"Favorable Review", "Fey Form", "Fly", "Forgotten Lines", "Gaseous Form", "Ghostly Tragedy", "Girzanje's March", "Glibness", "Globe of Invulernability",
"Hallucinatory Terrain", "Implement of Destruction", "Infectious Melody", "Internal Insurrection", "Invisibility Curtain", "Magic Mailbox", "Mirrors Misfortune",
"Modify Memory", "Morass of Ages", "Necrotic Radiation", "Nightmare", "Ocular Overload", "Outcast's Curse", "Painful Vibrations", "Pernicious Poltergeist",
"Phantasmal Killer", "Phatasmal Protagonist", "Private Sanctum", "Procyal Philosophy", "Ravenous Portal","Read Omens", "Rebounding Barrier", "Remove Curse", "Replicate",
"Resilient Sphere", "Rope Trick", "Sage's Curse", "Sanguine Mist", "Seal Fate", "Soft Landing","Spell Immunity", "Spiritual Anamnesis", "Spiritual Attunement",
"Suggestion", "Talking Corpse", "Telepathy", "Tortoise and the Hare", "Umbral Graft", "Vampiric Maiden", "Variable Gravity", "Veil","Vision of Beauty", "Winning Streak"};

vector<string> Occult_5th_Level = {"Abberant Form", "Abyssal Plague", "Bandit's Doom", "Banishment", "Belittling Boast", "Black Tentacles", "Blink Eyese", "Blinding Foam",
"Blink Charge", "Blister", "Blood Feast", "Chromatic Wall", "Cloak of Colors", "Crushing Despair", "Death Ward", "Dreaming Potential", "Ectoplasmic Expulsion",
"Etheric Shards", "False Vision", "Forceful Hand", "Glimmer of Charm", "Hallucination", "Illusory Scene", "Inevitable Disaster", "Infectious Comedy", "Invoke Spirits",
"Mariner's Curse", "Mind Probe", "Mirecloak","Mirror Malefactors", "Portrait of the Artist", "Prying Eye", "Quicken Time","Rallying Banner", "Ravening Maw",
"Repelling Pulse", "Return Beacon", "Rewinding Step", "Rip the Spirit", "Ritual Obstruction", "Scouring Pulse", "Secret Chest", "Sending", "Shadow Blast",
"Shadow Siphon", "Soulshelter Vessel", "Stagnate Time", "Strange Geometry", "Subconscious Suggestion", "Summon Entity", "Synaptic Pulse", "Synesthesia","Telekinetic Haul",
"Telepathic Bond", "Temporary Glyph", "Tongues", "Wall of Flesh"};

vector<string> Occult_6th_Level = {"Aura of the Unremarkable", "Awaken Entropy", "Blanket of Stars", "Blinding Fury","Bound in Death", "Cast into Time",
"Catch Your Name", "Chromatic Image", "Collective Transposition", "Dominate", "Feeblemind", "Hag's Fruit", "Lure Dream","Mislead", "Phatasmal Calamity", "Poltergeist's Fury",
"Ravenous Darkness","Repulsion","Scintillating Safegaurd","Scrying","Spellwrack","Spirit Blast","Suspended Retribution","Teleport","Temporal Ward","True Seeing",
"Unexpected Transposition", "Vampiric Exsanguination", "Vibrant Pattern", "Wall of Force","Word of Revision", "Zealous Conviction", "Zero Gravity"};

vector<string> Occult_7th_Level = {"Blightburn Blast", "Curse of the Spirit Orchestra","Dimensional Lock", "Duplicate Foe", "Energy Aegis", "Ethereal Jaunt", "Force Cage",
"Inexhastible Cynicism", "Leng Sting", "Mask of Terror", "Magnificent Mansion", "Maze of Locked Doors", "Momentary Recovery", "Plane Shift", "Posession", "Prismatic Armor",
"Prismatic Spray", "Project Image", "Retrocognition", "Return to Essence", "Reverse Gravity", "Shadow Raid", "Telekinetic Bombardment", "Tempest of Shades", "Time Beacon",
"True Target", "Visions of Danger", "Warp Mind"};

vector<string> Occult_8th_Level = {"Antimagic Field","Canticle of Everlasting Grief","Devour Life","Disaperrance","Discern Location","Dream Council","Falling Sky","Hypnopompic Terrors",
"Maze","Mind Blank","Prismatic Wall","Prying Survey", "Scintillating Pattern","Spirit Song","Spiritual Epidemic","Summon Irii","Uncontrollable Dance","Undermine Reality",
"Unrelenting Observation"};

vector<string> Occult_9th_Level = {"Astral Labyrinth", "Bilocation","Bind Soul", "Divinity Leech", "Foresight","Overwhelming Presence", "Prismatic Shield","Prismatic Sphere",
"Proliferating Eyes","Resplending Mansion","Summon Ancient Fleshforged","Telepathic Demand","Undertaker","Unfathomable Song","Unspeakable Shadow", "Voracious Gestalt", "Wail of the Banshee",
"Wierd"};

vector<string> Occult_10th_Level = {"Alter Reality","Fabricated Truth","Fated Confrontation","Gate","Indestructibility","Nullify","Remake","Shadow Army","Time Stop"};
#endif /* Occult_h */
