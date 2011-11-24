ofxPachube, v0.02
Made for openFrameworks 0.06

By
--
Carl-Johan Rosén
www.carljohanrosen.com


Dependencies
------------
- ofxThread
- Poco

Description
-----------
Pachube (www.pachube.com) is an online interface/api to share live data across the globe. This addon implements a part of the API and allows reading (output) and serving (input) data from and to feeds. Readign can be done as CSV or EEML, serving can be done only as CSV.

Due to some problems with threads+poco+windows there is an option to not use threads communication with Pachube. The good thing is that it doesn't crash on windows when "there is no internet connection available on application start". This is the only known situation where poco & threads have a problem in this addon. The drawback of not using threads is that the app hangs for a second or two when requesting information from a feed.

Please report comments, bugs and improvements to me if you like: cj dot rosen att gmail dot com