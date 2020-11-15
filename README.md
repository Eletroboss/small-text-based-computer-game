<h1>Running</h1>
<p>Please note that these binaries are compiled for x86_64. You will have to build yourself if you are using a 32-bit machine. For building, see <a href="#building">here</a>.</p>
<h2>All:</h2>
<ul><li>Please download both <code>basemap.dat</code> and <code>colmap.dat</code> from the release you want to use (v1.2.0+).</li>
   <li>For 2 player support, please download <code>2Player.sh</code> (v2.0.0+). For details on how to run in 2 player mode, please see <a href="#2p">here</a>.</li>
</ul>
<h2>UNIX:</h2>
<ul>
   <li> Download <code>main.o</code> from the relase that you want and put it in the same place as <code>colmap.dat</code> and <code>basemap.dat</code> (colmap and basemap are required as of 1.2.0).</li>
   <li> In the terminal run <code>main.o</code> using:</li>
   <pre><code>./main.o</code></pre>
</ul>
<p>NOTE: you may have to <code>chmod +x main.o</code> to run it.</p>
<h2>Windows:</h2>
<ul>
   <li>Download <code>main.exe</code> from the relase that you want and put it in the same place as <code>colmap.dat</code> and <code>basemap.dat</code> (colmap and basemap are required as of 1.2.0).</li>
   <li>Double-click <code>main.exe</code>.</li>
</ul>
<h2 id="2p">2 Player mode</h2>
<p>To run in 2 player mode, you need to:</p>
<ul>
   <li>Run <code>2Player.sh</code> with the username and ip/hostname of the local machine you're connecting to. E.G.:
      <pre><code>./2Player.sh user@192.168.x.x</code></pre>
      NOTE: you need password-less ssh access to the maching you're connecting to. Details on how to do this can be found <a href="http://www.linuxproblem.org/art_9.html">here</a>.</li>
   <li>Run <code>main.o</code> or <code>main.exe</code> with 1 or more arguments like so:</li>
   <pre><code>./main.o anyword
main.exe -0Hx bhU</code></pre>
</ul>
<p>Please note that 2 player mode is in development and very buggy and slow.</p>
<h1 id="building">Building</h1>
<h2>UNIX:</h2>
<ul><li>Run <code>make.sh</code> in <code>build/</code>. Make sure you have <code>gcc</code> installed.</li>
<li>binaries will be compiled to <code>bin/</code>.</li></ul>
<h2>Windows:</h2>
<ul><li>in the visual studio developer command prompt, run <code>make.bat</code> in <code>build/</code>.</li>
<li>binaries will be compiled to <code>bin/</code>.</li></ul>
