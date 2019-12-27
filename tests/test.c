/**
 * Main testing entry point. This class will systymatically run all testing classes that are associated with ULID.
 */
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>
#include <signal.h>

#include "test.h"

/* Starts the mock_lidar process that mimics */
int startMockLidar(void) {
    pid_t pid;
    
    // fork and start mock lidar process ...
    pid = fork();
    if(pid == 0) {
        printf("Starting mock lidar process ... ");
        execvp("./mock_lidar", 0);
        printf("ERROR: failed to initialize lidar with code -> %s\n",strerror(errno));
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
    
    int pid = startMockLidar();
    
    // Create list of pointer objects to be added during execution
    
    if(argc < 2){
        test_unit_message_file();
        test_unit_error_file();
        test_unit_socket_file();
        test_unit_qnode();
    }
    
    // Build function pointer array
    int i;
    for(i = 0; i < argc; i++){
        // tests message.c file
        if(!strcmp("-msg",argv[i]) || !strcmp("--msg",argv[i]) || !strcmp("-message",argv[i]) || !strcmp("--message",argv[i]))
            test_unit_message_file();
        
        // tests error.c file
        if(!strcmp("-err",argv[i]) || !strcmp("--err",argv[i]) || !strcmp("-error",argv[i]) || !strcmp("--error",argv[i]))
            test_unit_error_file();
        
        // tests socket.c file
        if(!strcmp("-sock",argv[i]) || !strcmp("--sock",argv[i]) || !strcmp("-socket",argv[i]) || !strcmp("--socket",argv[i]))
            test_unit_socket_file();
        
        if(!strcmp("-qnode",argv[i]) || !strcmp("--qnode",argv[i]))
            test_unit_qnode();
        
    }
    
    UNITY_BEGIN();
    
    // Loop through test pointers with callbacks
    for(i = 0; i < 5; i++) {
        // call array of function pointers
    }
    
    UNITY_END();
    
    endMockLidar(pid);
    
    return 0;
}
