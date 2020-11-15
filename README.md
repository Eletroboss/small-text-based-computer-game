<h1>Running</h1>
<p>Please note that these binaries are compiled for x86_64. You will have to build yourself if you are using a 32-bit machine. For building, see <a href="#building">here</a>.</p>
<h2>All:</h2>
<p>Please download both basemap.dat and colmap.dat from the release you want to use (v1.2.0+).<br />For 2 player support, please download 2Player.sh (v2.0.0+). For details on how to run in 2 player mode, please see <a href="#2p">here</a>.</p>
<h2>UNIX:</h2>
<ul>
   <li> Download main.o from the relase that you want and put it in the same place as colmap and basemap (colmap and basemap are needed as of 1.2.0).</li>
   <li> In the terminal run main.o using:</li>
   `./main.o`
</ul>
<p>NOTE: you may have to chmod +x main.o to run it.</p>
<h2>Windows:</h2>
<ul>
   <li>Download main.exe from the relase that you want and put it in the same place as colmap and basemap (colmap and basemap are needed as of 1.2.0).</li>
   <li>Double-click main.exe.</li>
</ul>
<h2 id="2p">2 Player mode</h2>
<p>To run in 2 player mode, you need to:</p>
<ul>
   <li>Run 2Player.sh with the username and ip/hostname of the local machine you're connecting to. E.G.:<br />./2Player.sh user@192.168.x.x<br />NOTE: you need password-less ssh access to the maching you're connecting to. Details on how to do this can be found <a href="http://www.linuxproblem.org/art_9.html">here</a>.</li>
   <li>Run main.o or main.exe with 1 or more arguments like so:</li>
   `./main.o 1`
   `main.exe 1`
</ul>
<p>Please note that 2 player mode is in development and very buggy and slow.</p>
<h1 id="building">Building</h1>
<h2>UNIX:</h2>
<p>Run make.sh in build/. Make sure you have gcc installed.</p>
<p>binaries will be compiled to bin/.</p>
<h2>
Windows:</h1>
<p> in the visual studio developer command prompt, run make.bat in build/.</p>
<p>binaries will be compiled to bin/.</p>
