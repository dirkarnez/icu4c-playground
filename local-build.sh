export PATH="/D/Softwares/x86_64-8.1.0-release-posix-seh-rt_v6-rev0/mingw64:/D/Softwares/x86_64-8.1.0-release-posix-seh-rt_v6-rev0/mingw64/bin:/D/Softwares/PortableGit-2.35.1.2-64-bit/mingw64/bin:/mingw64/bin:/usr/local/bin:/usr/bin:/bin:/mingw64/bin:/usr/bin" && 
gcc --version && ./configure mingw64 --disable-shared --enable-static --enable-64bit-libs --enable-release --disable-extras --disable-tools --disable-tests --disable-samples --enable-auto-cleanup --prefix="D:/icu4c-71_1-src/icu/source/icu-installation" && mingw32-make.exe install