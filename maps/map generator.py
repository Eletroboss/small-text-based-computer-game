import random
basemap = ["""\
########
########
########
########
########
########
######&#
########
""","""\
########
########
########
########
########
########
######&#
########
""","""\
########
######0#
########
####%%##
###%&%##
########
########
########
"""]
colmap = ["""\
rrrrrrrr
r      r
r      r
r      r
r      r
r      r
r     gr
rrrrrrrr
""","""\
rrrrrrrr
r r  r r
r r  r r
r r    r
r r  r r
r r  r r
r    rgr
rrrrrrrr
""","""\
rrrrrrrr
r r   gr
r   rrrr
r rrRR r
r rRgR r
r rrrr r
r      r
rrrrrrrr
"""]

basemap2 = [[' ']*8*9 for x in range(len(basemap))]
colmap2 = [[' ']*8*9 for x in range(len(colmap))]

for x in range(len(basemap)):
    for y in range(len(basemap[0])):
        if basemap[x][y] == "\n":
            basemap2[x][y] = "\\n"
        else:
            basemap2[x][y] = basemap[x][y]
        if colmap[x][y] == "\n":
            colmap2[x][y] = "\\n"
        else:
            colmap2[x][y] = colmap[x][y]

basemap3 = ""
colmap3 = ""

for x in range(len(basemap2)):
    for y in range(len(basemap2[0])):
        basemap3 += basemap2[x][y]
        colmap3 += colmap2[x][y]
    basemap3 += "\",\""
    colmap3 += "\",\""

CSource = "const char basemap["+str(len(basemap))+"]["+str(8*9)+"]={\""
CSource += basemap3[:-3]
CSource += "\"};const char colmap["+str(len(colmap))+"]["+str(8*9)+"]={\""
CSource += colmap3[:-3]
CSource += "\"};"
print(CSource)

file = open(r"C:\Users\Willi\Dropbox\Documents\programming\C\to be renamed\maps\maps.c","w")
file.write(CSource)
file.close()
