#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <curl/curl.h>

#define BUFFER_SIZE 10000

int write_callback(char *Buffer, int size, int n, char *userdata)
{
    strncat(userdata, Buffer, BUFFER_SIZE - strlen(userdata) - 1);
    return size * n;
}

bool check_phishing_site(char *url_to_check)
{
    CURL *curl;
    CURLcode res;
    char response[BUFFER_SIZE] = "";
    char *api_key = "";
    char api_url[256] = "https://urlscan.io/api/v1/scan/";

    curl = curl_easy_init();
    if (curl)
    {
        struct curl_slist *headers = NULL;
        headers = curl_slist_append(headers, "Content-Type: application/json");
        char api_header[256];
        snprintf(api_header, sizeof(api_header), "API-Key: %s", api_key);
        headers = curl_slist_append(headers, api_header);

        curl_easy_setopt(curl, CURLOPT_URL, api_url);
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

        char post_data[500];
        snprintf(post_data, sizeof(post_data), "{\"url\":\"%s\"}", url_to_check);
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, post_data);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, response);

        res = curl_easy_perform(curl);
        if (res != CURLE_OK)
        {
            curl_slist_free_all(headers);
            curl_easy_cleanup(curl);
            return false;
        }

        if (strstr(response, "phishing"))
        {
            return true;
        }
        else
        {
            return false;
        }

        curl_slist_free_all(headers);
        curl_easy_cleanup(curl);
    }
    else
    {
        return false;
    }
}
