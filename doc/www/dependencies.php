<? include ("barry.inc"); ?>

<? createHeader("barry - Software dependencies"); ?>

<? createSubHeader("System Specific"); ?>

<p>Fedora systems:
<ul>
	<li><b>ConsoleKit</b> - required for accessing the
		Blackberry without root privileges.</li>
</ul>
</p>

<p>Debian systems:
<ul>
	<li><b>fakeroot</b> - optional program to assist building your own
		Debian binary packages without root privileges</li>
</ul>
</p>

<p>OpenBSD systems:
<ul>
	<li><b>Uberry</b> - the uberry kernel module conflicts with the ugen
		interface that libusb uses to talk to the device.  To work
		around this, you will need to boot your kernel with "boot -c"
		and disable the uberry module.  Suggestions for better ways
		to work around this conflict are welcome.</li>
</ul>
</p>

<p>Mac OSX systems:
<ul>
	<li><b>gettext</b> - the default gettext autoconf scripts do not
		always do a very good job of detecting gettext and libintl
		libraries on the Mac.  If it cannot find libintl, it will
		automatically disable NLS support.  If this is important
		to you, add --with-libintl-prefix=/opt/local/ to the
		configure command line when building from source.</li>
</ul>
</p>

<? createSubHeader("Master List of Dependencies"); ?>

<p>The following list contains all software that Barry depends on, and
the reason for it.  Some are only needed for building the source, and
some are only needed for building CVS.

<ul>
	<li><b>C and C++ compilers</b> - 4.1.x or higher, for the tr1 includes (source build)</li>
	<li><b>ccache</b> - completely optional, but useful if you plan on compiling repeatedly</li>
	<li><b>pkg-config</b> (source build: so configure can autodetect library locations) </li>
	<li><b>libusb, stable (0.1.x)</b> - found at <a href="http://www.libusb.org/">http://www.libusb.org/</a> </li>
	<li><b>pthread</b>
	<li><b>boost</b> version 1.33 or higher (optional, Boost serialization support.) <a href="http://www.boost.org/">http://www.boost.org</a></li>
	<li><b>automake</b> version 1.9 (CVS builds only) </li>
	<li><b>autoconf</b> version 2.61 (CVS builds only) </li>
	<li><b>libtool</b> version 1.5.22 (CVS builds only) </li>
	<li><b>autopoint</b> on some systems, this is a separate package, yet
		on others, it is part of gettext (CVS builds only) </li>
	<li><b>doxygen</b> suggested version 1.5.6, only for building API documentation</li>
	<li><b>gtkmm, glademm, glibmm</b> C++ versions of the GTK libraries (needed for the barrybackup GUI)</li>
	<li><b>libtar</b> (barrybackup GUI) </li>
	<li><b>zlib</b>, needed for CRC32 checksums in library COD file support,
		and used by the barrybackup GUI</li>
	<li><b>libopensync</b> version 0.22 or, optionally, if building from source, latest opensync SVN tree </li>
	<li><b>sqlite, glib2, libxml2</b> (needed for syncing, required by OpenSync) </li>
	<li><b>libfuse</b> version 2.5 or higher (optional)</li>
	<li><b>libiconv</b>, needed for international charset conversions... most
		Linux distros have this as part of libc.  If you are using another
		OS such as FreeBSD, you'll have to install this separately.</li>
	<li><b>libxml++</b> version 2.6 for the desktop</li>
	<li><b>gettext</b>, needed for the iconv.m4 file, on some systems,
		when building from CVS to generate configure.</li>
	<li><b>php5</b>, needed for generating static HTML documentation (CVS builds only) </li>
	<li><b>rpmdevtools and rpm-build</b>, if building RPMs yourself</li>
	<li><b>fakeroot</b>, if building DEB packages yourself</li>
	<li><b>wxWidgets</b>, if building the Barry Desktop</li>
	<li><b>libgcal</b>, version 0.9.6 or higher, if building the
		Barry Desktop</li>
</ul>
</p>

<? createSubHeader("The Case of the Broken libtar"); ?>

<p>Well meaning people, in efforts to port the libtar examples to 64-bit
systems have introduced a bug that causes libtar to mismatch standard
read() and write() function call prototypes.</p>

<p>This bug has been seen in the Mandriva, ArchLinux, and Gentoo distros.
Depending on your system, and how up to date it is, it may already have been
fixed.</p>

<p>The curious can read more about this bug
<a href="http://www.mail-archive.com/barry-devel@lists.sourceforge.net/msg00746.html">here</a> and
<a href="http://www.mail-archive.com/barry-devel@lists.sourceforge.net/msg00754.html">here</a>.</p>

<p>Of course, you probably don't want to read the intricate details of
distro bugs.  You just want it to work!  For such systems, I usually
grab the libtar source RPM package from
<a href="ftp://ftp.nrc.ca/pub/systems/linux/redhat/fedora/linux/releases/10/Everything/source/SRPMS/libtar-1.2.11-11.fc10.src.rpm">here</a> and then run:
<pre>
rpmdev-setuptree (if this is your first time)
rpm -i libtar-1.2.11-11.fc10.src.rpm
cd ~/rpmbuild/SPECS
rpmbuild -ba libtar.spec
rpm -i ../RPMS/*/libtar*rpm
</pre>
</p>


<? createSubHeader("Dependency Packages for Common Distros"); ?>

<p>The following is a list of packages you'll need to install to build Barry
from source, if you are using one of the below common distributions.  Other
distributions should have similar package names.

<p>You can also find scripts to automate this in the source tree under
maintainer/depscripts.</p>

<ul>

<p><b>Fedora 11:</b></p>
<p>Use the yum package manager to install the following:
<ul>
	<li> pkgconfig </li>
	<li> libtool </li>
	<li> libusb-devel </li>
	<li> boost-devel (optional) </li>
	<li> libtar-devel </li>
	<li> gtkmm24-devel </li>
	<li> glibmm24-devel </li>
	<li> libglademm24-devel </li>
	<li> fuse-devel </li>
	<li> zlib-devel </li>
	<li> libxml++-devel </li>
	<li> gettext-devel </li>
	<li> libopensync-devel (0.22) </li>
	<li> ccache (optional) </li>
	<li> doxygen (optional) </li>
	<li> php-cli (optional, for generating docs) </li>
	<li> wxGTK-devel (optional, for Barry Desktop) </li>
</ul>

<p><b>Debian:</b></p>
<p>Use the apt-get package manager to install the following:
<ul>
	<li> pkg-config </li>
	<li> fakeroot </li>
	<li> cdbs </li>
	<li> autoconf </li>
	<li> automake </li>
	<li> autopoint (only on some newer Debian/Ubuntu systems) </li>
	<li> libtool </li>
	<li> libusb-dev </li>
	<li> libboost-serialization-dev </li>
	<li> libtar-dev </li>
	<li> libgtkmm-2.4-dev </li>
	<li> libglibmm-2.4-dev </li>
	<li> libglademm-2.4-dev </li>
	<li> libfuse-dev </li>
	<li> libxml++2.6-dev </li>
	<li> zlib1g-dev </li>
	<li> gettext </li>
	<li> libopensync0-dev </li>
	<li> ccache (optional) </li>
	<li> doxygen (optional) </li>
	<li> php5-cli (optional, for generating docs) </li>
	<li> libwxgtk2.8-dev and wx-common (optional, for Barry Desktop) </li>
</ul>

</ul>

