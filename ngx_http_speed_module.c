#include <ngx_config.h>
#include <ngx_core.h>
#include <ngx_http.h>
#include <stdio.h>

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
   h = (ngx_table_elt_t *)ngx_list_push(&r->headers_out.headers);
   if (h == NULL) {
         return NGX_HTTP_INTERNAL_SERVER_ERROR;
   }

   h->hash = 1;
   h->key.len = sizeof("Speed") - 1;
   h->key.data = (u_char *) "Speed";
   h->value.len = sizeof("speed") - 1;
   h->value.data = (u_char *) "speed";

   ngx_http_send_header(r);

   ngx_buf_t    *b;
   ngx_chain_t   *out;

   b = ngx_calloc_buf(r->pool);

   out = ngx_alloc_chain_link(r->pool);
   out->buf = b;
   out->next = NULL;

   return ngx_http_output_filter(r, out);
}

static char *ngx_http_speed(ngx_conf_t *cf, ngx_command_t *cmd, void *conf){
  ngx_http_core_loc_conf_t  *clcf;
  clcf = ngx_http_conf_get_module_loc_conf(cf, ngx_http_core_module);
  clcf->handler = ngx_http_speed_handler;
  return NGX_CONF_OK;
}
