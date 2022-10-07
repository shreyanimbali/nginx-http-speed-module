# nginx-http-speed-header-module

Module Overview
The NGINX Speed Detection Module aims at attaching a Speed (in kbps) header to the list
of Response Headers, provided the arguments : Bytes sent and Request Time.
Note that this does not indicate the speed of the current request or response.
It basically, serves as a template NGINX handler module where any output can be sent as a
Response Header, thereby making it highly expandable for various purposes involving
customised header services. NGINX provides an in-built add_header directive, but it can
only be used to display fixed keys and values in headers, and not headers that change
based on various situations and cases.
