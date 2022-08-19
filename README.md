# ColdSteelReantranslated
A mod that replaces every line of dialogue in Trails of Cold Steel with "Haha..."
![Preview Image](previewImage.png)
## How to Use
For the voice files, copy the contents of the assets folder into the root game directory (eg. C:\Program Files (x86)\Steam\steamapps\common\The Legend of Heroes - Trails of Cold Steel). **Doing this will replace the t_voice.tbl file located in data\text\data_us, back up the file before replacing it!**
For the hack itself, simply run the Injector executable and enter the path to your game (ed8.exe) and the mod DLL.
If you want to re-randomize the voice lines, take the unchanged *t_voices.tbl* and put it in the same directory as the voice file python script, which will do everything for you. Rename the newly created *t_voice_new.tbl* back to *t_voice.tbl* and put it in *data\text\data_us* in the game directory.
## Thing I might do (someday)
- Make it so replacing the t_voices.mdl and adding the custom voice files is not necessary
- Add an actual GUI to the injector
##Special Thanks to
https://gamehacking.academy/ - the site that has guides for learning basic game hacking, as well as a template for the injector used
