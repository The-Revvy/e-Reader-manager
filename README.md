# e-Reader Manager

NDS homebrew tool to inject `.raw` and `.bin` files into a Nintendo e-Reader.

# Usage
A Nintendo e-Reader is not able to fit into a DS Phat without a simple modification. However, it is able to fit into a DS Lite. If you are using a DS Phat, [click here for instructions on how to make it fit.](https://www.caitsith2.com/ereader/ereader_ds/ereader_ds_mod.htm)

Before this tool can be used, first-time setup is necessary:
* Erase saved data on your e-Reader (This can be done while holding L + R while it starts)
* Open the tool and select `FIRST-TIME SETUP`

Following this, usage is very simple:
* Place the `.raw` or `.bin` file of the e-Reader card you would like to inject onto your SD card
* Select `INJECT`
* Select the `.raw` or `.bin` file

# Credits
* DS save manager by Pokedoc,
with modifications by Admiral Curtiss
* CRC Calculator and NEDCLIB by CaitSith2
* .raw support by Admiral Curtiss
* Special thanks to Admiral Curtiss for making my garbage code good :)
# todo
* Add support for NES games and other multi-card applications. For the moment, you can use [this python script](https://github.com/The-Revvy/multi-card-combiner) to combine the data from several cards into one file (NES games will not work currently)

# Original Readme:

nds-savegame-manager
====================

NDS homebrew tool by Pokedoc to rip and restore saves from DS and GBA games. Small modifications by me to make it more user-friendly.

The code is published under the GNU GPL v2.

Below is a copy of the project description at https://code.google.com/p/savegame-manager/

-----

This tool allows you to backup and restore saves from commercial Nintendo handheld game cartridges. Based on the devkitPro toolchain and other open source libraries, this program implements most of the features also found in the older (closed-source and abandoned) tools developed by Rudolph and other members of the DS homebrew scene. It does not (and will never) support ROM dumping!

Requirements:
- A DLDI-capable Flash Card
- A Nintendo DS Phat/Lite. DSi and 3DS are not supported!

Features:
- Should support all known DS game saves, including Pokemon HG/SS/B/W, and probably that pedometer game as well
- Supports most GBA save types, with the exception of EEPROM type saves
- Supports 3in1 backup mode (requires an EZFlash 3in1), WiFi backup mode (requires a compatible access point and an FTP server)
- (soon) Translatable texts

If you want to use any of my code in a project using a different license, contact me, and we can work something out.