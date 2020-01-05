/**
 * Main testing entry point. This class will systymatically run all testing classes that are associated with ULID.
 */
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <errno.h>
#include <stdbool.h>
#include <stdlib.h>
#include <signal.h>
#include <limits.h>

#include "test.h"

/* Starts the mock_lidar process that mimics */
int startMockLidar(void) {
    pid_t pid;
    
    // Sets the path to the mock_lidar.exe file.
    char path[100];
    getcwd(path,100);
    if(!strcmp("SICK_Lidar_Unix-Linux",&(strrchr(path,'/')[1]))) {
        memset(path,0,100);
        strcat(path,"./tests/mock_lidar");
    } else if(!strcmp("tests",&(strrchr(path,'/')[1]))) {
        memset(path,0,100);
        strcat(path,"./mock_lidar");
    } else {
        printf("\n\n ERROR: incorrect path to start mock_lidar ... enter SICK_Lidar_Unix_Linux or tests directory.");
        exit(1);
    }
    
    // fork and start mock lidar process ...
    pid = fork();
    if(pid == 0) {
        printf("Starting mock lidar process ... \n");
        execvp(path, 0);
        printf("ERROR: failed to initialize lidar with code -> %s\n", strerror(errno));
        printf("\n MUST BE IN TEST FOLDER TO RUN TESTS \n\n");
        exit(1);
    }
    
    sleep(1);
    return pid;
}

void endMockLidar(int pid) {
    int status;
    
    if(kill(pid,SIGKILL) < 0)
        printf("ERROR: can't destory mock_lidar process with code --> %s\n",strerror(errno));
    
    while(pid != waitpid(pid, &status, 0))
        ;
}

void setUp(){}

void tearDown(){}

// not needed when using generate_test_runner.rb
int main(int argc, char * argv[]) {
    
    int i = 0, pid = 0;
    
    bool all_tests_enabled = false;
    bool message_test_enabled = false;
    bool error_test_enabled = false;
    bool socket_test_enabled = false;
    bool qnode_test_enabled = false;
    bool fifo_test_enabled = false;
    
    if(argc < 2){
        all_tests_enabled = true;
    } else {
        for(i = 0; i < argc; i++){
            if(!strcmp("-msg",argv[i]) || !strcmp("--msg",argv[i]) || !strcmp("-message",argv[i]) || !strcmp("--message",argv[i]))
                message_test_enabled = true;
            if(!strcmp("-err",argv[i]) || !strcmp("--err",argv[i]) || !strcmp("-error",argv[i]) || !strcmp("--error",argv[i]))
                error_test_enabled = true;
            if(!strcmp("-sock",argv[i]) || !strcmp("--sock",argv[i]) || !strcmp("-socket",argv[i]) || !strcmp("--socket",argv[i]))
                socket_test_enabled = true;
            if(!strcmp("-qnode",argv[i]) || !strcmp("--qnode",argv[i]))
                qnode_test_enabled = true;
            if(!strcmp("-fifo",argv[i]) || !strcmp("--fifo",argv[i]))
                fifo_test_enabled = true;
        }
    }
    
    if(socket_test_enabled || all_tests_enabled)
        pid = startMockLidar();
    
    /* Starting Unity tests */
    UNITY_BEGIN();
    
    if(all_tests_enabled){
        test_unit_message_file();
        test_unit_error_file();
        test_unit_socket_file();
        test_unit_qnode();
        test_unit_fifo();
    } else {
        if(message_test_enabled)
            test_unit_message_file();
        if(error_test_enabled)
            test_unit_error_file();
        if(socket_test_enabled)
            test_unit_socket_file();
        if(qnode_test_enabled)
            test_unit_qnode();
        if(fifo_test_enabled)
            test_unit_fifo();
    }
    
    UNITY_END();
    
    if(socket_test_enabled || all_tests_enabled)
        endMockLidar(pid);
    
    return 0;
}