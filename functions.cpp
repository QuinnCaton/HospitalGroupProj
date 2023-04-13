#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <string>
#include "functions.h"
#include "Patient.h"
#include <iomanip>

//include global static variable to keep track of number of each kind of patient
static int patientCount[3]= {0, 0, 0};
//patientCount[0] = number of Heart Clinic Patients
//patientCount[1] = number of Lung Clinic Patients
//patientCount[2] = number of Plastic Surgery Patients

using namespace std;


void ReadData(vector<vector<Patient>>& allPatients, vector<Patient>& heartClinic, vector<Patient>& plasticSurgeryClinic, vector<Patient>& lungClinic){
    ifstream fin;
    ofstream fout;//added
    string testChar, tempStr, firstName, lastName, SocSecNum;
    fin.open("patient.csv");
    fout.open("log.txt");//added
    string line;
    vector<string>row;
    Patient hospitalPatient;

    while(fin.good()){
        getline(fin, line);
        testChar=line.substr(0, 2);

        if(testChar=="Q"){
            break;
        }

        row.clear();
        stringstream inSS(line);
        while(getline(inSS, tempStr, ',')){
            row.push_back(tempStr);
        }

        if(testChar=="PC"){
            //patient clinic--where lung clinic patients go? PC==Pulminary Clinic
            firstName= row[1];
            lastName= row[2];
            SocSecNum= row[3];
            hospitalPatient.setType("Lung");
            hospitalPatient.setFName(firstName);
            hospitalPatient.setLName(lastName);
            hospitalPatient.setSSN(stoi(SocSecNum));
            hospitalPatient.setCritNo();
            fout<<"Lung Clinic: "<<firstName<<" "<<lastName<<" "<<SocSecNum<<endl;//added

            lungClinic.push_back(hospitalPatient);
            patientCount[1]+=1;

        }else if(testChar=="HC") {
            //heart clinic
            firstName= row[1];
            lastName= row[2];
            SocSecNum= row[3];
            hospitalPatient.setType("Heart");
            hospitalPatient.setFName(firstName);
            hospitalPatient.setLName(lastName);
            hospitalPatient.setSSN(stoi(SocSecNum));
            hospitalPatient.setCritNo();
            fout<<"Heart Clinic: "<<firstName<<" "<<lastName<<" "<<SocSecNum<<endl;//added

            heartClinic.push_back(hospitalPatient);
            patientCount[0]+=1;

        }else if(testChar=="PS") {
            //plastic surgery
            firstName= row[1];
            lastName= row[2];
            SocSecNum= row[3];
            hospitalPatient.setType("Plastic");
            hospitalPatient.setFName(firstName);
            hospitalPatient.setLName(lastName);
            hospitalPatient.setSSN(stoi(SocSecNum));
            hospitalPatient.setCritNo();
            fout<<"Plastic Surgery: "<<firstName<<" "<<lastName<<" "<<SocSecNum<<endl;//added

            plasticSurgeryClinic.push_back(hospitalPatient);
            patientCount[2]+=1;

        }else{
            fout<<"Error! unknown status"<<endl;
        }
    }

    //Push onto vector of vectors here
    allPatients.push_back(lungClinic);
    allPatients.push_back(heartClinic);
    allPatients.push_back(plasticSurgeryClinic);
    fout.close();
}


//subMenu
void subMenu (string department, vector<vector<Patient>>& allPatients, vector<vector<string>>& transactionLog){

    cout << "Welcome to the " << department << endl;
    cout <<"1: - Add Patient" << endl;
    cout <<"2: - Add Critical Patient" << endl;
    cout <<"3: - Take out Patient for Operation" << endl;
    cout <<"4: - Cancel Patient" << endl;
    cout <<"5: - List Patients in Queue" << endl;
    cout <<"6: - Change Department or exit" << endl;

    int option;
    cout << "Enter your choice: ";
    cin >> option;
    cout << endl;

    switch (option){
        case 1:
            //Add Patient
            if(department=="Heart Clinic"){
                addPatient(allPatients, transactionLog, department);
            }else if(department=="Lung Clinic"){
                addPatient(allPatients, transactionLog, department);
            }else if(department=="Plastic Surgery Clinic"){
                addPatient(allPatients, transactionLog, department);
            }
            break;
        case 2:
            //Add Critical Patient
            if(department=="Heart Clinic"){
                addCriticalPatient(allPatients, transactionLog, department);
            }else if(department=="Lung Clinic"){
                addCriticalPatient(allPatients, transactionLog, department);
            }else if(department=="Plastic Surgery Clinic"){
                addCriticalPatient(allPatients, transactionLog, department);
            }

            break;
        case 3:
            //Take out 
            break;
        case 4:
            //cancel Patient
            break;
        case 5:
            //List Patients in Queue
            if(department=="Heart Clinic"){
              cout<<"Patients in the Heart Clinic:"<<endl;
                cout<<"First Name"<<setw(12)<<"Last Name"<<setw(5)<<"SSN"<<setw(8)<<"Status"<<endl;
                for(int i=0;i<allPatients.size();++i){
                    for(int j=0;j<allPatients.at(i).size();++j){
                        if(allPatients[i][j].getType()=="Heart"){
                             cout<<left<<setw(13)<<allPatients[i][j].getFName();
                            cout<<setw(11)<<allPatients[i][j].getLName();
                            if(allPatients[i][j].getSSN()<10){
                                cout<<"00"<<setw(3)<<allPatients[i][j].getSSN();
                            }else if(allPatients[i][j].getSSN()>=10&&allPatients[i][j].getSSN()<100){
                                cout<<"0"<<setw(4)<<allPatients[i][j].getSSN();
                            }else if(allPatients[i][j].getSSN()>=100){
                                cout<<setw(4)<<allPatients[i][j].getSSN()<<" ";
                            }

                            if(allPatients[i][j].isCrit()){
                                cout<<"CRITICAL";
                            }else{
                                cout<<"reg";
                            }
                            cout<<endl;
                        }
                    }
                }
            }

            if(department=="Lung Clinic"){
              cout<<"Patients in the Lung Clinic:"<<endl;
                cout<<"First Name"<<setw(12)<<"Last Name"<<setw(5)<<"SSN"<<setw(8)<<"Status"<<endl;
                for(int i=0;i<allPatients.size();++i){
                    for(int j=0;j<allPatients.at(i).size();++j){
                        if(allPatients[i][j].getType()=="Lung"){
                            cout<<left<<setw(13)<<allPatients[i][j].getFName();
                            cout<<setw(11)<<allPatients[i][j].getLName();
                            if(allPatients[i][j].getSSN()<10){
                                cout<<"00"<<setw(3)<<allPatients[i][j].getSSN();
                            }else if(allPatients[i][j].getSSN()>=10&&allPatients[i][j].getSSN()<100){
                                cout<<"0"<<setw(4)<<allPatients[i][j].getSSN();
                            }else if(allPatients[i][j].getSSN()>=100){
                                cout<<setw(4)<<allPatients[i][j].getSSN()<<" ";
                            }

                            if(allPatients[i][j].isCrit()){
                                cout<<"CRITICAL";
                            }else{
                                cout<<"reg";
                            }
                            cout<<endl;
                        }
                    }
                }
            }

            if(department=="Plastic Surgery Clinic"){
              cout<<"Patients in the Plastic Surgery Clinic:"<<endl;
                cout<<"First Name"<<setw(12)<<"Last Name"<<setw(5)<<"SSN"<<setw(8)<<"Status"<<endl;
                for(int i=0;i<allPatients.size();++i){
                    for(int j=0;j<allPatients.at(i).size();++j){
                        if(allPatients[i][j].getType()=="Plastic"){
                            cout<<left<<setw(13)<<allPatients[i][j].getFName();
                            cout<<setw(11)<<allPatients[i][j].getLName();
                            if(allPatients[i][j].getSSN()<10){
                                cout<<"00"<<setw(3)<<allPatients[i][j].getSSN();
                            }else if(allPatients[i][j].getSSN()>=10&&allPatients[i][j].getSSN()<100){
                                cout<<"0"<<setw(4)<<allPatients[i][j].getSSN();
                            }else if(allPatients[i][j].getSSN()>=100){
                                cout<<setw(4)<<allPatients[i][j].getSSN()<<" ";
                            }

                            if(allPatients[i][j].isCrit()){
                                cout<<"CRITICAL";
                            }else{
                                cout<<"reg";
                            }
                            cout<<endl;
                        }
                    }
                }


            }
            break;
        case 6:
            //Change Department or Exist
            break;
        default:
            cout << "Invalid entry, please try again." << endl;

    }
}

void addPatient(vector<vector<Patient>>& allPatients, vector<vector<string>>& log, string HospDepartment){

    Patient hospitalPatient;
    vector<Patient> tempHeartClinic;
    vector<Patient> tempLungClinic;
    vector<Patient> tempPlasticSurgeryClinic;
    string firstName, lastName, type, socSecNum;
    string transaction;
    cin.exceptions(istream::failbit | istream::badbit);
    int checkVal;
    ///Checking each clinic amount
    ///Delete when finished
    cout<<"Heart"<<endl;
    cout<<patientCount[0]<<endl;
    cout<<"Lung"<<endl;
    cout<<patientCount[1]<<endl;
    cout<<"Plastic"<<endl;
    cout<<patientCount[2]<<endl;
    if(HospDepartment == "Heart Clinic"){
      checkVal = patientCount[0];
    }
    if(HospDepartment == "Lung Clinic"){
      checkVal = patientCount[1];
    }
    if(HospDepartment == "Plastic Surgery Clinic"){
      checkVal = patientCount[2];
    }

  try{
    if(checkVal >= 10){
        cout<<"Sorry, clinic is at full capacity. Please try again later."<<endl;
    }
    else {
        cin.ignore();
        cout << "First Name: ";
        getline(cin, firstName);

        cout << "Last Name: ";
        getline(cin, lastName);

        cout << "SSN: ";
        getline(cin, socSecNum);
        transaction = firstName + " " + lastName + " added to " + 
          HospDepartment + " queue.";

        if (socSecNum == "") {
            cout << "New patient entry cancelled." << endl;

        } else {
            if (HospDepartment == "Heart Clinic") {
                hospitalPatient.setType("Heart");
                hospitalPatient.setLName(lastName);
                hospitalPatient.setFName(firstName);
                hospitalPatient.setSSN(stoi(socSecNum));
                hospitalPatient.setCritNo();
                allPatients.at(1).push_back(hospitalPatient);
                patientCount[0] += 1;
                cout << transaction << endl;
                log[0].push_back(transaction);

            } else if (HospDepartment == "Lung Clinic") {
                hospitalPatient.setType("Lung");
                hospitalPatient.setLName(lastName);
                hospitalPatient.setFName(firstName);
                hospitalPatient.setSSN(stoi(socSecNum));
                hospitalPatient.setCritNo();
                allPatients.at(0).push_back(hospitalPatient);
                patientCount[1] += 1;
                cout << transaction << endl;
                log[1].push_back(transaction);

            } else if (HospDepartment == "Plastic Surgery Clinic") {
                hospitalPatient.setType("Plastic");
                hospitalPatient.setLName(lastName);
                hospitalPatient.setFName(firstName);
                hospitalPatient.setSSN(stoi(socSecNum));
                hospitalPatient.setCritNo();
                allPatients.at(2).push_back(hospitalPatient);
                patientCount[2] += 1;
                cout << transaction << endl;
                log[2].push_back(transaction);
            }
        }
    }
  }
	catch (...) {
		transaction = "Error occured trying to add patient " + firstName + " " + lastName;
    cout << transaction << endl;
    log[3].push_back(transaction);
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
	}
}

void addCriticalPatient(vector<vector<Patient>>& allPatients, vector<vector<string>>& log, string HospDepartment){
    int checkVal;
    Patient hospitalPatient;
    vector<Patient> tempHeartClinic;
    vector<Patient> tempLungClinic;
    vector<Patient> tempPlasticSurgeryClinic;
    string firstName, lastName, type, socSecNum;
    string transaction;
    cin.exceptions(istream::failbit | istream::badbit);
    ///Checking each clinic amount
    ///Delete when finished
    cout<<"Heart"<<endl;
    cout<<patientCount[0]<<endl;
    cout<<"Lung"<<endl;
    cout<<patientCount[1]<<endl;
    cout<<"Plastic"<<endl;
    cout<<patientCount[2]<<endl;
    
    if(HospDepartment == "Heart Clinic"){
      checkVal = patientCount[0];
    }
    if(HospDepartment == "Lung Clinic"){
      checkVal = patientCount[1];
    }
    if(HospDepartment == "Plastic Surgery Clinic"){
      checkVal = patientCount[2];
    }
  try{
    if(checkVal >= 10){
        cout<<"Sorry, clinic is at full capacity. Please try again later."<<endl;
    }else {
        cin.ignore();
        cout << "First Name: ";
        getline(cin, firstName);

        cout << "Last Name: ";
        getline(cin, lastName);

        cout << "SSN: ";
        getline(cin, socSecNum);
        transaction = firstName + " " + lastName + " added to " + 
          HospDepartment + " queue.";
        if (socSecNum == "") {
            cout << "New patient entry cancelled." << endl;

        } else {
            if (HospDepartment == "Heart Clinic") {
                hospitalPatient.setType("Heart");
                hospitalPatient.setLName(lastName);
                hospitalPatient.setFName(firstName);
                hospitalPatient.setSSN(stoi(socSecNum));
                hospitalPatient.setCritYes();
                allPatients.at(1).push_back(hospitalPatient);
                sortPatient(allPatients.at(1));
                patientCount[0] += 1;
                cout << transaction << endl;
                log[0].push_back(transaction);

            } else if (HospDepartment == "Lung Clinic") {
                hospitalPatient.setType("Lung");
                hospitalPatient.setLName(lastName);
                hospitalPatient.setFName(firstName);
                hospitalPatient.setSSN(stoi(socSecNum));
                hospitalPatient.setCritYes();
                allPatients.at(0).push_back(hospitalPatient);
                sortPatient(allPatients.at(0));
                patientCount[1] += 1;
                cout << transaction << endl;
                log[1].push_back(transaction);

            } else if (HospDepartment == "Plastic Surgery Clinic") {
                hospitalPatient.setType("Plastic");
                hospitalPatient.setLName(lastName);
                hospitalPatient.setFName(firstName);
                hospitalPatient.setSSN(stoi(socSecNum));
                hospitalPatient.setCritYes();
                allPatients.at(2).push_back(hospitalPatient);
                sortPatient(allPatients.at(2));
                patientCount[2] += 1;
                cout << transaction << endl;
                log[2].push_back(transaction);
            }
        }
    }
  }
  	catch (...) {
      transaction = "Error occured trying to add patient " + firstName + " " + lastName;
      cout << transaction << endl;
      log[3].push_back(transaction);
      cin.clear();
      cin.ignore(numeric_limits<streamsize>::max(), '\n');
	}
}


void takeOutPatient(vector<vector<Patient>>& v, string s) {
  
}

void cancelPatient(vector<Patient>& v, vector<vector<string>>& l, string s) {

  
}

void sortPatient(vector<Patient>& patientQueue){
  vector<Patient> newPatientQueue(0);
  //Copies crit patients to front of new queue
  for(int i = 0; i < patientQueue.size(); ++i){
    if(patientQueue.at(i).isCrit()){
      newPatientQueue.push_back(patientQueue.at(i));
    }
  }
  //Copies general patients to back of new queue
  for(int j = 0; j < patientQueue.size(); ++j){
    if(!patientQueue.at(j).isCrit()){
      newPatientQueue.push_back(patientQueue.at(j));
    }
  }
  //Copies patients back to queue passed into function
  for(int n = 0; n < patientQueue.size(); ++n){
    patientQueue.at(n) = newPatientQueue.at(n);
  }
}