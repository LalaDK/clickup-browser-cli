#include <stdio.h>
#include <curl/curl.h>
#include "http_helper.h"
#include <json-c/json.h>
#include <json-c/json_tokener.h>

CURL *curl;
CURLcode result;
struct curl_slist *chunk;

struct json_object *parsed_json;
struct json_tokener* tokener;

struct json_object *http_helper_get_json(char *url) {
  tokener = json_tokener_new();
  curl = curl_easy_init();

  if(curl) {
    chunk = curl_slist_append(chunk, "authorization: pk_4538266_UTM4B3A3SVENYTJ8JW2LMCUGDMG69FMK");
    chunk = curl_slist_append(chunk, "Content-Type: application/json");
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, chunk);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writefunc);
    //curl_easy_setopt(curl, CURLOPT_URL, "https://api.clickup.com/api/v2/list/8212783/task?archived=false");
    curl_easy_setopt(curl, CURLOPT_URL, url);

    result = curl_easy_perform(curl);
    if(result != CURLE_OK) {
      fprintf(stderr, "curl_easy_perform() failed: %s\n",
      curl_easy_strerror(result));
    }
    curl_easy_cleanup(curl);
    curl_slist_free_all(chunk);
  }
  return parsed_json;
}

size_t writefunc(void *ptr, size_t size, size_t nmemb) {
  char* c_arr = (char*) ptr;
  parsed_json = json_tokener_parse_ex(tokener, c_arr, nmemb);
  return nmemb;
}
