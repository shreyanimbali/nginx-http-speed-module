#include <ngx_config.h>
#include <ngx_core.h>
#include <ngx_http.h>
#include <stdio.h>
#include <math.h>

static char *ngx_http_speed(ngx_conf_t *cf, ngx_command_t *cmd, void *conf);

static ngx_command_t  ngx_http_speed_commands[] = {
  {
    ngx_string("speed"),
    NGX_HTTP_LOC_CONF|NGX_CONF_NOARGS,
    ngx_http_speed,
    0,
    0,
    NULL
  },
    ngx_null_command
};

static ngx_http_module_t  ngx_http_speed_module_ctx = {
  NULL,
  NULL,
  NULL,
  NULL,
  NULL,
  NULL,
  NULL,
  NULL
};

ngx_module_t ngx_http_speed_module = {
  NGX_MODULE_V1,
  &ngx_http_speed_module_ctx,
  ngx_http_speed_commands,
  NGX_HTTP_MODULE,
  NULL,
  NULL,
  NULL,
  NULL,
  NULL,
  NULL,
  NULL,
  NGX_MODULE_V1_PADDING
};

static ngx_int_t ngx_http_speed_handler(ngx_http_request_t *r){
    ngx_table_elt_t *h;
    h = ngx_list_push(&r->headers_out.headers);
    if (h == NULL) {
          return NGX_ERROR;
    }
    u_char *ngx_hello_world = r->args.data;
    size_t sz = r->args.len;

    r->headers_out.content_type.len = strlen("text/html");
    r->headers_out.content_type.data = (u_char *) "text/html";
    r->headers_out.status = NGX_HTTP_OK;
    r->headers_out.content_length_n = sz;
    h->hash = 1;
  
    h->key.len = sizeof("Speed (in kbps)") - 1;
    h->key.data = (u_char *) "Speed (in kbps)";
    h->value.len = sz;
    h->value.data = ngx_hello_world;
    ngx_http_send_header(r);

    ngx_buf_t    *b;
    ngx_chain_t   *out;

    b = ngx_calloc_buf(r->pool);

    out = ngx_alloc_chain_link(r->pool);
    out->buf = b;     
    out->next = NULL;

    b->pos = ngx_hello_world;
    b->last = ngx_hello_world + sz;
    b->memory = 1;
    b->last_buf = 1;
    h->hash = 1;
    ngx_http_send_header(r);
    return ngx_http_output_filter(r, out);
}

static char *ngx_http_speed(ngx_conf_t *cf, ngx_command_t *cmd, void *conf){
  ngx_http_core_loc_conf_t  *clcf;
  clcf = ngx_http_conf_get_module_loc_conf(cf, ngx_http_core_module);
  clcf->handler = ngx_http_speed_handler;
  return NGX_CONF_OK;
}
