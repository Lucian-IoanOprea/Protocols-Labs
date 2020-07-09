#include <openssl/ssl.h>
#include <openssl/bio.h>
#include <openssl/err.h>

#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>

int main()
{
    BIO * bio;
    SSL * ssl;
    SSL_CTX * ctx;
    int p;
    char * request = "GET / HTTP/1.0\r\nHost: www.verisign.com\r\n\r\n";
    char r[1024];

    /* initializare librarie */

    SSL_library_init ();
    ERR_load_BIO_strings();
    SSL_load_error_strings();
    OpenSSL_add_all_algorithms();

    /* TO DO initializare context */
    ctx = SSL_CTX_new(SSLv23_client_method());

    /* incarca trust store */

    if(! SSL_CTX_load_verify_locations(ctx, "TrustStore.pem", NULL))
    {
        fprintf(stderr, "Error loading trust store\n");
        ERR_print_errors_fp(stderr);
        SSL_CTX_free(ctx);
        return 0;
    }

    /* stabileste conexiune */
    bio = BIO_new_ssl_connect(ctx);
   
    /* Seteaza flag SSL_MODE_AUTO_RETRY  */

    BIO_get_ssl(bio, & ssl);
    SSL_set_mode(ssl, SSL_MODE_AUTO_RETRY);

    /* TO DO setup conexiune */
    BIO_set_conn_hostname(bio, "verisign.com:443");

    /* TO DO verifica certificat */
    if (BIO_do_connect(bio) <= 0) {
        BIO_free_all(bio);
        SSL_CTX_free(ctx);
        return -1;
    }

    /* Trimite request */

    BIO_write(bio, request, strlen(request));

    /* TO DO Citeste raspuns si pregateste  output*/
    int fd = open("display.html", O_TRUNC | O_WRONLY | O_CREAT, 0644);
    
    if (fd < 0) {
        fprintf(stderr, "Nu s-a putut deschide fisierul\n");
        BIO_free_all(bio);
        SSL_CTX_free(ctx);
        exit(EXIT_FAILURE);
    }

    memset(r, 0, sizeof(r));
    int read_bytes;
    while ((read_bytes = BIO_read(bio, r, 1024)) > 0) {
        write(fd, r, read_bytes);
        memset(r, 0, sizeof(r));
    }
   /* Inchide conexiune si elibereaza context */

    BIO_free_all(bio);
    SSL_CTX_free(ctx);
    close(fd);
    return 0;
}
