#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>
void main(int argc, char *argv[]){
    int socket_desc;
    struct sockaddr_in server; //socket adress bilgilerini tutan struct
    char *message,server_reply[2000];

    socket_desc=socket(AF_INET,SOCK_STREAM,0);
    /* Socket olusturulur,ilk parametre adress ailesini belli eder(ipv4),
    2. parametre soket tipini belirtir (SOCK_STREAM=>TCP protokolune uyumlu),
    3. parametre protokolü belirtir(0=> IP protokol)
    */
    if (socket_desc==-1){
        printf("Soket olusturulamadi ...\n");
    }
    
    server.sin_addr.s_addr=inet_addr("74.125.235.20");//ip adresi
    server.sin_family=AF_INET;//ip türü(ip 4)
    server.sin_port=htons(80);//Port numarasi
    if (connect(socket_desc,(struct sockaddr *)&server,sizeof(server))<0)//Sockete baglanir
    {
        puts("Baglanti hatasi...\n");
        return;
    }
    puts("baglanti saglandi...\n");
    
    message="GET / HTTP/1.1\r\n\r\n"; //socket üzerinden gönderilcek mesajdir.Iceriginin anlamamı baglanilan porta karsilik gelen web sitesinin ana sayfasina gitmemizi saglar

    if(send(socket_desc,message,strlen(message),0)<0)//socket üzerinden baglanilen ip adresine mesaj yollanir
    {
        puts("Komut yollanamadi...\n");
    }
    puts("Komut iletildi...\n");

    if (recv(socket_desc,server_reply,2000,0)<0)
    {
        puts("Veri alinamadi\n");
    }

    puts("Okunan veri: ");
    puts(server_reply);
    close(socket_desc);
    
    return;
}
