basemap = ["""\
########\
########\
########\
########\
########\
########\
######&#\
########\
""","""\
########\
########\
########\
########\
########\
########\
######&#\
########\
""","""\
########\
######0#\
########\
####%%##\
###%&%##\
########\
########\
########\
""","""\
########\
######0#\
########\
####%%%#\
###%&%%#\
######%#\
##%%%%%#\
########\
""","""\
########\
######0#\
#####%##\
###%####\
###%####\
#%#%##%#\
#####%&#\
########
"""]
colmap = ["""\
rrrrrrrr\
r      r\
r      r\
r      r\
r      r\
r      r\
r     gr\
rrrrrrrr\
""","""\
rrrrrrrr\
r r  r r\
r r  r r\
r r    r\
r r  r r\
r r  r r\
r    rgr\
rrrrrrrr\
""","""\
rrrrrrrr\
r r   gr\
r   rrrr\
r rrRR r\
r rRgR r\
r rrrr r\
r      r\
rrrrrrrr\
""","""\
rrrrrrrr\
r r   gr\
r   rrrr\
r rrRRRr\
r rRgRRr\
r rrrrRr\
r RRRRRr\
rrrrrrrr\
""","""\
rrrrrrrr\
r r rrgr\
r    R r\
rr Rrr r\
r  R   r\
rR R  Rr\
r    Rgr\
rrrrrrrr
"""]



basemap2 = ""
colmap2 = ""

for x in range(len(basemap)):
    for y in range(len(basemap[0])):
        basemap2 += basemap[x][y]
        colmap2 += colmap[x][y]
    basemap2 += "\",\""
    colmap2 += "\",\""

CSource = "const unsigned char basemapVar["+str(len(basemap))+"][500]={\""
CSource += basemap2[:-3]
CSource += "\"};const unsigned char colmapVar["+str(len(colmap))+"][500]={\""
CSource += colmap2[:-3]
CSource += "\"};"
CSource += "unsigned char basemap(unsigned char x, unsigned char y){return basemapVar[x][y];}unsigned char colmap(int x,int y){return colmapVar[x][y];}"
print(CSource)

file = open(r"maps.c","w")
file.write(CSource)
file.close()
