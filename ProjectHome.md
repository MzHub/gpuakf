This program implements an automatic image and video abstraction technique based on the anisotropic Kuwahara filter. It was written by [Jan Eric Kyprianidis](http://www.kyprianidis.com) while working as a research scientist for the [computer graphics systems group](http://www.hpi3d.de) of the [Hasso-Plattner-Institut](http://www.hpi.uni-potsdam.de) at the University of Potsdam, Germany.

A detailed discussion of the implementation can be found in the [GPU Pro](http://gpupro.blogspot.com) book (Kyprianidis & et al., 2010). For more details on technical aspects see (Kyprianidis et al., 2009).

![http://wiki.gpuakf.googlecode.com/git/screenshot.jpg](http://wiki.gpuakf.googlecode.com/git/screenshot.jpg)


## Building ##

Building requires the [Qt cross platform toolkit](http://qt.nokia.com).
Recommended Qt version is 4.7.2. The program has been tested to successfully build with Visual Studio 2008 on Windows, Qt Creator SDK 2.1.0 on Mac OS X and the default toolchain on Ubuntu 10.10. See build.bat/build.sh to get started. Video processing is only available on Mac OS X and Windows and requires Apple [QuickTime](http://www.apple.com/quicktime). The Apple QuickTime SDK for Windows can be downloaded [here](http://developer.apple.com/quicktime).

## Related Publications ##

  * [Kyprianidis, J. E.](http://www.kyprianidis.com), [Kang, H.](http://www.cs.umsl.edu/~kang/), & [Döllner, J.](http://www.hpi3d.de) (2009). [Image and Video Abstraction by Anisotropic Kuwahara Filtering](http://www.kyprianidis.com/pg2009.html). _Computer Graphics Forum_ 28(7). (Special issue on Pacific Graphics 2009)
  * [Kyprianidis, J. E.](http://www.kyprianidis.com), [Kang, H.](http://www.cs.umsl.edu/~kang/), & [Döllner, J.](http://www.hpi3d.de) (2010). [Anisotropic Kuwahara Filtering on the GPU](http://www.kyprianidis.com/gpupro.html). In W. Engel (Ed.), _[GPU Pro](http://gpupro.blogspot.com) - Advanced Rendering Techniques. AK Peters_.
  * [Kyprianidis, J. E.](http://www.kyprianidis.com), [Semmo, A.](http://www.amirsemmo.de), [Kang, H.](http://www.cs.umsl.edu/~kang/), & [Döllner, J.](http://www.hpi3d.de) (2010). [Anisotropic Kuwahara Filtering with Polynomial Weighting Functions](http://www.kyprianidis.com/tpcg2010.html). In _Proc. EG UK Theory and Practice of Computer Graphics_.