const unsigned char basemapVar[5][500]={"######################################################&#########        ","######################################################&#########        ","##############0#############%%#####%&%##########################        ","##############0#############%%%####%&%%#######%###%%%%%#########        ","##############0######%#####%#######%#####%#%##%######%&#########        "};const unsigned char colmapVar[5][500]={"rrrrrrrrr      rr      rr      rr      rr      rr     grrrrrrrrr        ","rrrrrrrrr r  r rr r  r rr r    rr r  r rr r  r rr    rgrrrrrrrrr        ","rrrrrrrrr r   grr   rrrrr rrRR rr rRgR rr rrrr rr      rrrrrrrrr        ","rrrrrrrrr r   grr   rrrrr rrRRRrr rRgRRrr rrrrRrr RRRRRrrrrrrrrr        ","rrrrrrrrr r rrgrr    R rrr Rrr rr  R   rrR R  Rrr    Rgrrrrrrrrr        "};unsigned char basemap(unsigned char x,unsigned char y){return basemapVar[x][y];}unsigned char colmap(int x,int y){return colmapVar[x][y];}