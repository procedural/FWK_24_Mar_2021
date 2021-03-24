// network framework
// - rlyeh, public domain

int download(FILE *out, const char *url);

// int send_game_state(void *ptr, int len, int flags); PROTOCOL_V1|QUANTIZE|COMPRESS|RLE
// int recv_game_state(); compensate, extrapolate, intrapolate(); lerp();

#ifdef NETWORK_C
#pragma once

#if 0
#if defined(_WIN32)
#   include <winsock2.h>
#   include <wininet.h>
#   pragma comment(lib,"wininet.lib")
#endif

int download(FILE *out, const char *url) {
#ifdef _WIN32
    DWORD ok = 0, lBytesRead = 0;
    HINTERNET session = InternetOpenA("request 1", PRE_CONFIG_INTERNET_ACCESS, NULL, INTERNET_INVALID_PORT_NUMBER, 0);
    if( session ) {
        HINTERNET request = InternetOpenUrlA(session, url, NULL, 0, INTERNET_FLAG_RELOAD, 0);
        if( request ) {
            enum { buflen = 4096 };
            char buffer[ buflen ];
            for(; (ok = (InternetReadFile(request, buffer, buflen, &lBytesRead) != FALSE) && lBytesRead > 0); ) {
                ok = 1 == fwrite(buffer, lBytesRead, 1, out);
                if( !ok ) break;
            }
            InternetCloseHandle(request);
        }
        InternetCloseHandle(session);
    }
    return ok && !lBytesRead;
#else
    return 0;
#endif
}
#endif

int download(FILE *out, const char *url) {
    https_t *h = https_get("https://www.google.com/", NULL);
    while (!https_process(h)) sleep_ms(1);
        //printf("%d %s\n\n%.*s\n", h->status_code, h->content_type, (int)h->response_size, (char*)h->response_data);
        bool ok = fwrite(h->response_data, 1, h->response_size, out) == 1;
    https_release(h);
    return ok;
}

#endif // DOWNLOAD_C
