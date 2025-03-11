#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <curl/curl.h>

int callback(char *res_data, int size, int n, char *data)
{
    strcat(data, res_data);
    return size * n;
}
bool check_phishing_site(const char *url, const char *api_key)
{
    CURL *curl;
    CURLcode res;
    char response[50000] = "";
    char api_url[1024];
    strcat(api_url, "https://safebrowsing.googleapis.com/v4/threatMatches:find?key=");
    strcat(api_url, api_key);
    char post_data[1024];
    snprintf(post_data, sizeof(post_data), "{"
                                           "  \"client\": {"
                                           "    \"clientId\": \"your-client-id\","
                                           "    \"clientVersion\": \"1.0\""
                                           "  },"
                                           "  \"threatInfo\": {"
                                           "    \"threatTypes\": [\"MALWARE\", \"SOCIAL_ENGINEERING\"],"
                                           "    \"platformTypes\": [\"WINDOWS\", \"ANDROID\", \"IOS\"],"
                                           "    \"threatEntryTypes\": [\"URL\"],"
                                           "    \"threatEntries\": [{\"url\": \"%s\"}]"
                                           "  }"
                                           "}",
             url);
    curl_global_init(CURL_GLOBAL_ALL);
    curl = curl_easy_init();
    if (curl)
    {
        curl_easy_setopt(curl, CURLOPT_URL, api_url);
        struct curl_slist *headers = NULL;
        headers = curl_slist_append(headers, "Content-Type: application/json");
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
        curl_easy_setopt(curl, CURLOPT_POST, 1);
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, post_data);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, callback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, response);
        res = curl_easy_perform(curl);
        if (res == CURLE_OK)
        {
            if (strstr(response, "\"matches\"") != NULL)
            {
                return true;
            }
            else
            {
                return false;
            }
        }
        curl_slist_free_all(headers);
        curl_easy_cleanup(curl);
    }

    curl_global_cleanup();
}
