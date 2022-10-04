#include <stdio.h>
#include <stdlib.h>
#include <curl/curl.h>
#include<jansson.h>

void function_pt(void *ptr, size_t size, size_t nmemb, void *stream){
  printf("\n\n%s\n\n", ptr);
  // printf("%d", atoi(ptr));

  json_t *js_obj      = json_loads(ptr, 0, NULL);
  json_t *js_name  = json_object_get(js_obj, "name");
  json_t *js_main  = json_object_get(js_obj, "main");
  json_t *js_temp    = json_object_get(js_main, "temp");
  json_t *js_humidity = json_object_get(js_main, "humidity");

  printf("Country    = %s\n", json_is_string(js_name) ?
          json_string_value(js_name) : "unknown");
  char snum[5];

  printf("Temperature = %.2f Deg Celc.\n", json_is_number(js_temp) ?
          json_number_value(js_temp) : 0);
  printf("Humidity = %.2f Percent\n\n", json_is_number(js_humidity) ?
          json_number_value(js_humidity) : 0);
}

int main(void)
{
  CURL *curl;
  curl = curl_easy_init();
  if(curl) {
    curl_easy_setopt(curl, CURLOPT_URL, "api.openweathermap.org/data/2.5/weather?q=Virginia&units=metric&appid=c1b8806bdf9a75f4841a04169649f404"); //43e048eba3a93833bba04ffd0120ff17 //c1b8806bdf9a75f4841a04169649f404
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, function_pt);
    curl_easy_perform(curl);
    curl_easy_cleanup(curl);
  }
  system("pause");
  return 0;
}