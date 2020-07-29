pipeline {
    agent { label '192.168.50.92' }
    triggers {
        pollSCM('H/2 * * * *')
    }
    options {
        disableConcurrentBuilds();
    }
    environment {
        REMOTE_REPO_ADDR='192.168.50.92'
        REMOTE_REPO_DIR='/home/botson/jenkins'
    }
    stages {
        stage('setup') {
            steps {
                echo 'setup'
                sh script: "pwd"
            }
        }
        stage('build') {
            steps {
                sh script: "pwd"
                sh script: "./build.sh"
            }
        }
        stage('run') {
            steps {
                withEnv(['DISPLAY=:0']) {
                    sh script: "export DISPLAY=:0"
                    sh script: "./autorun.sh"
                }
            }
        }
        stage('compare') {
            steps {
                sh script: "./autocompare.sh nvidia"
            }
        }
    }
}

