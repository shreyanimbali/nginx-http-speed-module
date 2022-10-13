# nginx-http-speed-header-module

## Module Overview

The NGINX Speed Detection Module aims at attaching a Speed (in kbps) header to the list of Response Headers, provided the arguments : Bytes sent and Request Time.

Note that this does not indicate the speed of the current request or response.

It basically, serves as a template NGINX handler module where any output can be sent as a Response Header, thereby making it highly expandable for various purposes involving customised header services. NGINX provides an in-built add_header directive, but it can only be used to display fixed keys and values in headers, and not headers that change based on various situations and cases.

## A few major components of a handler NGINX module:

**ngx_http_speed_commands** : 
is a static array of module directives. In this module, we only have one module directive names "speed". Each element in this array is of the type ngx_command_t .

**ngx_http_speed_module_ctx** : 
is an array of function references. Even if you do not need this array of functions that will be executed for various purposes such as pre-configuration, post configuration, etc., you still have to defile it with all values being NULL.

**ngx_http_speed_module** : 
is an array of definitions for the module which tells us where the above two arrays are.

**ngx_http_speed_handler** : 
This is the main function in our module. Note: And handler function must always have a return type of ngx_int_t and should have only one argument, which is a pointer of the type ngx_http_request_t.

After sending the custom made and set headers, we set the body of our response using ngx_buf_t (buffer) and ngx_chain_t (chain link). The body is then sent using ngx_http_output_filter(r,out).
