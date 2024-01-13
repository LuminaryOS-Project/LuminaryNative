# Might be useful...?
build_64:
	g++ -c -m64 -fPIC -IC:\Users\samue\.jdks\azul-17.0.8.1\include -IC:\Users\samue\.jdks\azul-17.0.8.1\include\win32 me_intel_dev_TestJNI.cpp -o me_intel_dev_TestJNI.o 

link_64:
	g++ -shared -m64 -o native.dll me_intel_dev_TestJNI.o -Wl,--add-stdcall-alias

main:
	g++ -c -IC:\Users\samue\.jdks\azul-17.0.8.1\include -IC:\Users\samue\.jdks\azul-17.0.8.1\include\win32 LuminaryNative.cpp
	g++ -shared -o windows.dll LuminaryNative.o

