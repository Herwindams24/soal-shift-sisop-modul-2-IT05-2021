#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <wait.h>
#include <string.h>
#include <dirent.h>
#include <time.h>
#include <errno.h>
#include <dirent.h>
#include <fcntl.h>
 
int main(int argc, char *argv[])
{
    if (argc != 2 || argv[1][1] != 'z' && argv[1][1] != 'x')
        printf("argumen hanya -z atau -x");
 
    pid_t child_id, child_id2;
    char cwd[100];
    getcwd(cwd, sizeof(cwd));
    int status;
    int test;
    int pid2 = getpid();
 
    child_id = fork();
    //     printf("%d\n", child_id);
    if (child_id < 0)
        exit(EXIT_FAILURE);
 
    if (child_id == 0)
    {
        FILE *ptr;
        char files[100];
        char data[1000];
        char dst[100];
        char src[100];
        char mode[100];
 
        sprintf(src, "%s/killer.sh", cwd);
        sprintf(dst, "%s/killer", cwd);
 
        sprintf(files, "%s/killer.sh", cwd);
 
        if (argv[1][1] == 'z')
            strcpy(mode, " char *argv[] = {\"killall\", \"-s\", \"9\", \"soal2\", NULL};");
        else if (argv[1][1] == 'x')
            sprintf(mode, " char *argv[] = {\"kill\", \"%d\", NULL};", pid2);
 
        sprintf(data, "#include <stdlib.h>\n"
                      "#include <sys/types.h>\n"
                      "#include <unistd.h>\n"
                      "#include <stdio.h>\n"
                      "#include <wait.h>\n"
                      "#include <string.h>\n"
 
                      " int main() {"
                      " pid_t child_id;"
                      " int status;"
 
                      " child_id = fork();"
                      " if (child_id < 0) exit(EXIT_FAILURE);"
 
                      " if (child_id == 0) {"
                      " %s"
                      " execv(\"/usr/bin/killall\", argv);"
                      " } else {"
                      " while (wait(&status)>0);"
                      " }"
                      " }",
                mode);
 
        ptr = fopen(files, "w");
        fputs(data, ptr);
        fclose(ptr);
 
        char *argv[] = {"gcc", src, "-o", dst, NULL};
        execv("/usr/bin/gcc", argv);
    }
 
    while (wait(&status) > 0)
        ;
 
    child_id2 = fork();
    //     printf("%d\n", child_id2);
    if (child_id2 < 0)
        exit(EXIT_FAILURE);
 
    if (child_id2 == 0)
    {
        char src[100];
 
        sprintf(src, "%s/killer.sh", cwd);
        char *argv[] = {"rm", src, NULL};
        execv("/bin/rm", argv);
    }
 
    while (wait(&status) > 0)
        ;
 
    pid_t pid, sid; // Variabel menyimpan PID
 
    pid = fork(); // Menyimpan PID dari Child Process
 
    /* Keluar saat fork gagal
    * (nilai variabel pid < 0) */
    if (pid < 0)
    {
        exit(EXIT_FAILURE);
    }
 
    /* Keluar saat fork berhasil
    * (nilai variabel pid adalah PID dari child process) */
    if (pid > 0)
    {
        exit(EXIT_SUCCESS);
    }
 
    umask(0);
 
    sid = setsid();
    if (sid < 0)
    {
        exit(EXIT_FAILURE);
    }
 
//    close(STDIN_FILENO);
//    close(STDOUT_FILENO);
//    close(STDERR_FILENO);

while (1)
{
    pid_t child1, child2, child3, child4;
    int status;
 
    time_t now;
    struct tm *t;
    char buffer[80];
 
    time(&now);
    t = localtime(&now);
 
    strftime(buffer, 80, "%Y-%m-%d_%H:%M:%S", t);
    // puts (buffer);
    char *dir = buffer;
    mkdir(dir, 0777);
 
    child1 = fork();
    if (child1 < 0)
        exit(EXIT_FAILURE);
 
    if (child1 == 0)
    {
        for (int i = 0; i < 10; i++)
        {
            if (fork() == 0)
            {
                unsigned long get_time = (unsigned long)time(NULL);
                get_time = (get_time % 1000) + 50;
 
                char link[50];
                sprintf(link, "https://picsum.photos/%ld", get_time);
 
                time_t filet;
                struct tm *fileti;
                char files[80] = "";
                char down_dir[100];
 
                time(&filet);
                fileti = localtime(&filet);
 
                strftime(files, 80, "%Y-%m-%d_%H:%M:%S", fileti);
                sprintf(down_dir, "%s/%s", buffer, files);
                // puts(down_dir);
 
                char *argv[] = {"wget", "-O", down_dir, link, NULL};
                execv("/usr/bin/wget", argv);
                exit(0);
            }
            sleep(5);
        }
        for (int i = 0; i < 10; i++)
            wait(NULL);
    }
 
    while (wait(&status) > 0)
        ;
 
    child2 = fork();
    if (child2 < 0)
        exit(EXIT_FAILURE);
 
    if (child2 == 0)
    {
        char zip_name[100];
        sprintf(zip_name, "%s.zip", buffer);
 
        char *argv[] = {"zip", "-rm", zip_name, buffer, NULL};
        execv("/usr/bin/zip", argv);
        exit(0);
    }
 
    while (wait(&status) > 0)
        ;
    sleep(40);
}
}
