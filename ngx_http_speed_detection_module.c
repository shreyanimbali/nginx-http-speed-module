#include <ngx_core.h>
#include <ngx_config.h>
#include <ngx_http.h>
#include <stdio.h>

typedef struct{
   ngx_flag_t         enable;
}ngx_http_speed_detection_conf_t;

static void *ngx_http_speed_detection_create_conf(ngx_conf_t *cf);
static char *ngx_http_speed_detection_merge_conf(ngx_conf_t *cf, void *parent, void *child);
static ngx_int_t ngx_http_speed_detection_init(ngx_conf_t *cf);

static ngx_command_t  ngx_http_speed_detection_commands[] = {
 { ngx_string("speed_detection"),
 NGX_HTTP_MAIN_CONF|NGX_HTTP_SRV_CONF|NGX_HTTP_LOC_CONF|NGX_CONF_FLAG,
 ngx_conf_set_flag_slot,
 NGX_HTTP_LOC_CONF_OFFSET,
 offsetof(ngx_http_speed_detection_conf_t, enable),
 NULL },

 ngx_null_command

};
 
static ngx_http_module_t  ngx_http_speed_detection_module_ctx = {
 NULL,                                    /* proconfiguration */
 ngx_http_speed_detection_init,           /* postconfiguration */
 
 NULL,                                    /* create main configuration */
 NULL,                                    /* init main configuration */
 
 NULL,                                    /* create server configuration */
 NULL,                                    /* merge server configuration */
 
 ngx_http_speed_detection_create_conf,                                   /* create location configuration */
 ngx_http_speed_detection_merge_conf                                    /* merge location configuration */
};

ngx_module_t  ngx_http_speed_detection_module = {
 NGX_MODULE_V1,
 &ngx_http_speed_detection_module_ctx, /* module context */
 ngx_http_speed_detection_commands,    /* module directives */
 NGX_HTTP_MODULE,                       /* module type */
 NULL,                                  /* init master */
 NULL,                                  /* init module */
 NULL,                                  /* init process */
 NULL,                                  /* init thread */
 NULL,                                  /* exit thread */
 NULL,                                  /* exit process */
 NULL,                                  /* exit master */
 NGX_MODULE_V1_PADDING
};
 
static ngx_http_output_header_filter_pt ngx_http_next_header_filter;

static ngx_int_t ngx_http_speed_detection_header_filter(ngx_http_request_t *r){
   
   ngx_http_speed_detection_conf_t  *conf;
   conf = ngx_http_get_module_loc_conf(r, ngx_http_speed_detection_module);

   if (!conf->enable){
      return ngx_http_next_header_filter(r);
   }

   ngx_log_debug0(NGX_LOG_DEBUG_HTTP, r->connection->log, 0,"compose header filter");

   //ngx_http_upstream_state_t *u;
   ngx_table_elt_t *h;
   //off_t bytes = r->headers_out.content_length_n;
   //ngx_int_t kilobits = bytes * 0.008;
   //ngx_msec_t response_msec = (u->response_time) - (u->header_time);
   //off_t byte_sent = &u->bytes_sent;
   //r->request_length;
   //ngx_int_t response_sec = response_msec * 0.001;
   //ngx_int_t speed = kilobits / response_sec;
   h = ngx_list_push(&r->headers_out.headers);
   if(h==NULL){
    return NGX_ERROR;
   }
   h->hash = 1;
   //int kilobitsInt = kilobits;
   //char kilobitsStr[20];

   //sprintf(kilobitsStr,"%d",kilobitsInt);
   //ngx_str_set(&h->key, "Kilobits");
   //ngx_str_set(&h->value, kilobitsStr);

   ngx_str_set(&h->key, "Speed");
   ngx_str_set(&h->value, "speed");
   return ngx_http_next_header_filter(r);
}

static void *
ngx_http_speed_detection_create_conf(ngx_conf_t *cf)
{
    ngx_http_speed_detection_conf_t  *conf;

    conf = ngx_pcalloc(cf->pool, sizeof(ngx_http_speed_detection_conf_t));
    if (conf == NULL) {
        return NULL;
    }

    conf->enable = NGX_CONF_UNSET;

    return conf;
}

static char *
ngx_http_speed_detection_merge_conf(ngx_conf_t *cf, void *parent, void *child)
{
    ngx_http_speed_detection_conf_t *prev = parent;
    ngx_http_speed_detection_conf_t *conf = child;

    ngx_conf_merge_value(conf->enable, prev->enable, 0);

    return NGX_CONF_OK;
}

static ngx_int_t ngx_http_speed_detection_init(ngx_conf_t *cf){
   ngx_http_next_header_filter = ngx_http_top_header_filter;
   ngx_http_top_header_filter = ngx_http_speed_detection_header_filter;
   return NGX_OK;
}
