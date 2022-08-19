from random import randint

with open('voiceFiles.txt', 'r') as f:
    files = f.read()
    fileList = files.splitlines()

fileNameTypes = [b'e8v', b'p28v', b'pc2v', b'pc8v']
with open('t_voice.tbl', 'rb') as f:
    file = bytearray(f.read())
    for i in range(len(file)):
        a = file[i:i+3]
        b = file[i:i+4]
        c = file[i:i+12]
        if file[i : i+3] in fileNameTypes or file[i : i+4] in fileNameTypes:
            if file[i+8] == 0:
                file[i : i+8] = bytes(fileList[randint(0, 9)], encoding='ascii')
            elif file[i+9] == 0:
                file[i : i+9] = bytes(fileList[randint(10, 19)], encoding='ascii')
            elif file[i+10] == 0:
                file[i : i+10] = bytes(fileList[randint(20, 29)], encoding='ascii')
            elif file[i+11] == 0:
                file[i : i+11] = bytes(fileList[randint(30, 39)], encoding='ascii')
            elif file[i+12] == 0:
                file[i : i+12] = bytes(fileList[randint(40, 49)], encoding='ascii')

with open('t_voice_new.tbl', 'wb') as f:
    f.write(file)