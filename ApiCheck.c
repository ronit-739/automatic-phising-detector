#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <curl/curl.h>
#define BUFFER_SIZE 10000
size_t write_callback(void *ptr, size_t size, size_t nmemb, void *userdata)
{
    strncat((char *)userdata, (char *)ptr, BUFFER_SIZE - strlen(userdata) - 1);
    return size * nmemb;
}

int ApiCheck(char *url_to_check)
{
    CURL *curl;
    CURLcode res;
    char response[BUFFER_SIZE] = "";
    char *api_key = "";
    char api_url[256] = "https://safebrowsing.googleapis.com/v4/threatMatches:find?key=";
    strcat(api_url, api_key);
    char post_data[500];
    snprintf(post_data, sizeof(post_data),
             "{"
             "\"client\": {\"clientId\": \"yourapp\", \"clientVersion\": \"1.0\"},"
             "\"threatInfo\": {"
             "\"threatTypes\": [\"MALWARE\", \"SOCIAL_ENGINEERING\"],"
             "\"platformTypes\": [\"ANY_PLATFORM\"],"
             "\"threatEntryTypes\": [\"URL\"],"
             "\"threatEntries\": [{\"url\": \"%s\"}]"
             "}"
             "}",
             url_to_check);
    curl = curl_easy_init();
    if (curl)
    {
        curl_easy_setopt(curl, CURLOPT_URL, api_url);
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, post_data);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, response);
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, (struct curl_slist *)curl_slist_append(NULL, "Content-Type: application/json"));

        res = curl_easy_perform(curl);
        if (res != CURLE_OK)
        {
            return false;
        }
        else
        {
            if (strstr(response, "\"matches\""))
            {
                return false;
            }
            else
            {
                return true;
            }
        }

        curl_easy_cleanup(curl);
    }
    else
    {
        printf("Failed to initialize cURL.\n");
    }

    return 0;
}
