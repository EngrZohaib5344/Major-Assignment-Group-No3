#include <iostream>
#include <string>
using namespace std;

class Doctor {
	public:
                 string name;
                 string specialty;
                 string shift;
                 int fees;
                 string unavailableDays[7];
                 int unavailableDayCount;

         Doctor() : unavailableDayCount(0) {}

        Doctor(string& n,string& s,string& sh,int& fe,string unav[], int unavCount)
        : name(n), specialty(s), shift(sh),fees(fe), unavailableDayCount(unavCount) {
        for (int i = 0; i < unavCount; ++i) {
            unavailableDays[i] = unav[i];
        }
    }
};

class Patient {
	public:
    	       	string name;
    		int age;
    		string gender;
    		bool admitted;
    		int wardNumber;

    		Patient() : admitted(false), wardNumber(-1) {}

    		Patient(string& n, int a, string& g)
        		: name(n), age(a), gender(g), admitted(false), wardNumber(-1) {}
};

class Ward {
public:
    int total;
    int reserved;

    Ward() : total(10), reserved(0) {}

    void assignPatient() {
        reserved++;
    }

    void dischargePatient() {
        if (reserved > 0) {
            reserved--;
        }
    }

    int getFreeWards() const {
        return total - reserved;
    }
};

class Appointment_doctor {
public:
    Patient patient;
    Doctor doctor;
    string date;

    Appointment_doctor() {}

    Appointment_doctor( Patient& p,  Doctor& d, string& dt)
        : patient(p), doctor(d), date(dt) {}
};

class Hospital {
public:
    Doctor doctors[10];
    Patient patients[10];
    Appointment_doctor appointments[10];
    Ward ward;

    int doctorCount;
    int patientCount;
    int appointmentCount;

    Hospital() : doctorCount(0), patientCount(0), appointmentCount(0) {}

    void registerDoctor(Doctor& doctor) {
        if (doctorCount < 10) {
            doctors[doctorCount++] = doctor;
        } else {
            cout << "Cannot register more doctors. Limit reached.\n";
        }
    }

    void registerPatient(const Patient& patient) {
        if (patientCount < 10) {
            patients[patientCount++] = patient;
        } else {
            cout << "Cannot register more patients. Limit reached.\n";
        }
    }

    void Appointmentschedule( Patient& patient, Doctor& doctor,string& date) {
        if (appointmentCount < 10) {
            appointments[appointmentCount++] = Appointment(patient, doctor, date);
        } else {
            cout << "Cannot schedule more appointments. Limit reached.\n";
        }
    }

    void displayAppointments() const {
        cout << "Appointments:\n";
        for (int i = 0; i < appointmentCount; ++i) {
            cout << "Date: " << appointments[i].date << "\n";
            cout << "Patient: " << appointments[i].patient.name << "\n";
            cout << "Doctor: " << appointments[i].doctor.name << " (Specialty: " << appointments[i].doctor.specialty << ")\n";
            cout << "------------------------\n";
        }
    }

    int countAvailableWards() const {
        return ward.getFreeWards();
    }

    void assignWardToPatient(Patient& patient) {
        if (patient.admitted) {
            cout << "Patient " << patient.name << " is already admitted to Ward " << patient.wardNumber << ".\n";
            return;
        }

        if (ward.getFreeWards() > 0) {
            ward.assignPatient();
            patient.admitted = true;
            patient.wardNumber = ward.reserved;
            cout << "Patient " << patient.name << " assigned to Ward " << patient.wardNumber << ".\n";
        } else {
            cout << "No available wards. Cannot admit patient.\n";
        }
    }

    void dischargePatientFromWardToNEw(Patient& patient) {
        if (patient.admitted) {
            ward.dischargePatient();
            patient.admitted = false;
            cout << "Patient " << patient.name << " discharged from Ward " << patient.wardNumber << ".\n";
            patient.wardNumber = -1;
        } else {
            cout << "Patient the patient is discharge form now  " << patient.name << " is not admitted to any ward.\n";
        }
    } 

    void displayAvailableDoctors(string& shift,string& day) {
        cout << "\nAVAILABLE DOCTERS:\n";
        for (int i = 0; i < doctorCount; ++i) {
            bool isUnavailable = false;
            for (int j = 0; j < doctors[i].unavailableDayCount; ++j) {
                if (doctors[i].unavailableDays[j] == day) {
                    isUnavailable = true;
                    break;
                }
            }
            if (doctors[i].shift == shift && !isUnavailable) {
                cout<<"\nDoctor: " << doctors[i].name ;
	      cout<<"\nSpecialty: " <<"("<< doctors[i].specialty << ")";
	      cout<<"\nFees : "<<doctors[i].fees;
            }
        }
    }
    void prescribeMedicine(Patient& patient,  std::string& medicine) {
        cout << "Prescribing " << medicine << " to patient " << patient.name << ".\n";
    }
    void getWardInfo() const {
        cout << "Total Wards: " << ward.total << "\n";
        cout << "Reserved Wards: " << ward.reserved << "\n";
        cout << "Free Wards: " << ward.getFreeWards() << "\n";
    }
};

int main() {
    Hospital hospital;
    int choice;
    
        cout<<"\n+-------------------------+\n";
        cout << "\n  LIFE CARE HOSPITAL\n";
        cout<<"\n+-------------------------+\n";
    do{  
        cout<<"\n----+-----+-----+----+----+----+----+\n";
        cout << "1. Register Doctor\n";
        cout << "2. Register Patient\n";
        cout << "3. Schedule Appointment\n";
        cout << "4. View Appointments\n";
        cout << "5. Number of Wards\n";
        cout << "6. Available Doctors\n";
        cout << "7. Prescribe Medicine\n";
        cout << "8. Admit Patient & Assign Ward to Patient\n";
        cout << "9. Discharge Patient & Discharge Patient from Ward\n";
        cout << "0. Exit\n";
        cout<<"\n---+--+---+---+---+--+--+--+---+---+--+---+----+---+--+--+\n";
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore(); // Clear the newline from buffer

        switch (choice) {
            case 1: {
                string name, specialty, shift;
                int fee;
                string unavailableDays[7];
                int day_Count;
                char choice;
	do{
                cout << "Enter Your Doctor's Name: ";
                getline(cin, name);
                cout << "Enter Your Doctor's Specialty: ";
                getline(cin, specialty);
                cout << "Enter Your Doctor's Fees: ";
                cin >> fee;
                cin.ignore(); // Clear the newline from buffer
                cout << "Enter Doctor's Shift (morning/night): ";
                getline(cin, shift);

                cout << "Enter the number of days the doctor is unavailable: ";
                cin >> day_Count;
                cin.ignore(); // Clear the newline from buffer

                cout << "Enter the unavailable days (e.g., Monday Tuesday): ";
                for (int i = 0; i < day_Count; ++i) {
                    getline(cin, unavailableDays[i]);
                }

                Doctor doctor(name, specialty, shift,fee, unavailableDays, day_
                    Count);
                hospital.registerDoctor(doctor);
                cout<<"\nDOCTOR REGISTER SUCCESSFULLY!";
                cout<<"\n+---+---+---+---+---+---+---+---+---+---+\n";
	      cout<<"\nDO YOU WANT TO ADD MORE DOCTOR( Y (yes) / N (not) ) : ";
	      cin>>choice;
	      cin.ignore(); // Clear the newline from buffer
	      choice=tolower(choice);      
      }while(choice=='y');
                break;
            }
            case 2: {
                string name, gender;
                int age;
                char choice;
          do{
	
                cout << "Enter Patient's Name: ";
                getline(cin, name);
                cout << "Enter Patient's Age: ";
                cin >> age;
                cin.ignore(); // Clear the newline from buffer
                cout << "Enter Patient's Gender: ";
                getline(cin, gender);
                Patient patient(name, age, gender);
                hospital.registerPatient(patient);
                cout << "\nPATIENT REGISTER SUCCESSFULLY\n";
	      cout<<"\nDO YOU WANT ADD MORE PATIENTS:";
	      cin>>choice;
	      cin.ignore(); // Clear the newline from buffer
	      choice=tolower(choice);	
	}while(choice=='y');
	      break;
            }
            case 3: {
                string patientName, doctorName, date;
                cout << "Enter Patient's Name: ";
                getline(cin, patientName);
                cout << "Enter Doctor's Name: ";
                getline(cin, doctorName);
                cout << "Enter Appointment Date (DD-MM-YYYY): ";
                getline(cin, date);

                Doctor selectedDoctor;
                Patient selectedPatient;
                bool doctorFound = false;
                bool patientFound = false;

                for (int i = 0; i < hospital.doctorCount; ++i) {
                    if (hospital.doctors[i].name == doctorName) {
                        selectedDoctor = hospital.doctors[i];
                        doctorFound = true;
                        break;
                    }
                }

               for (int i = 0; i < hospital.patientCount; ++i) {
                    if (hospital.patients[i].name == patientName) {
                        selectedPatient = hospital.patients[i];
                        patientFound = true;
                        break;
                    }
                }

                if (doctorFound && patientFound) {
                    hospital.scheduleAppointment(selectedPatient, selectedDoctor, date);
                    cout << "\nAPPOINTMENT SCHEDULED SUCCESSFULLY!\n";
                } else {
                    if (!doctorFound) {
                        cout << "\nDOCTOR NOT FOUND. PLEASE CHECK THE NAME AND TRY AGAIN.\n";
                    }
                    if (!patientFound) {
                        cout << "\nPATIENT NOT FOUND. PLEASE CHECK THE NAME AND TRY AGAIN.\n";
                    }
                }
                break;
            }
            case 4: {
                hospital.displayAppointments();
                break;
            }
            case 5: {
                hospital.getWardInfo();
                break;
            }
            case 6: {
                string shifts, days;
                cout << "Enter Shift (morning/night): ";
                getline(cin, shifts);
                cout << "Enter Day: ";
                getline(cin, days);
                hospital.displayAvailableDoctors(shifts, days);
                break;
            }
            case 7: {
                string patientName, medicine;
                cout << "Enter Patient's Name: ";
                getline(cin, patientName);
                cout << "Enter Prescribed Medicine: ";
                getline(cin, medicine);

                bool patientFound = false;
                for (int i = 0; i < hospital.patientCount; ++i) {
                    if (hospital.patients[i].name == patientName) {
                        hospital.prescribeMedicine(hospital.patients[i], medicine);
                        patientFound = true;
                        break;
                    }
                }

                if (!patientFound) {
                    cout << "PATIENT NOT FOUND. PLEASE CHECK THE NAME AND TRY AGAIN.\n";
                }
                break;
            }
            case 8: {
                string patientName;
                cout << "Enter Patient's Name: ";
                getline(cin, patientName);

                bool patientFound = false;
                for (int i = 0; i < hospital.patientCount; ++i) {
                    if (hospital.patients[i].name == patientName) {
                        hospital.assignWardToPatient(hospital.patients[i]);
                        patientFound = true;
                        break;
                    }
                }

                if (!patientFound) {
                    cout << "PATIENT NOT FOUND.PLEASE CHECK THE  NAME AND TRY AGAIN.\n";
                }
                break;
            }
            case 9: {
                string patientName;
                cout << "Enter Patient's Name: ";
                getline(cin, patientName);

                bool patientFound = false;
                for (int i = 0; i < hospital.patientCount; ++i) {
                    if (hospital.patients[i].name == patientName) {
                        hospital.dischargePatientFromWard(hospital.patients[i]);
                        patientFound = true;
                        break;
                    }
                }

                if (!patientFound) {
                    cout << "\nPATIENT NOT FOUND PLEASE CHECK THE NAME AND TRY AGAIN.\n";
                }
                break;
            }
            case 0: {
                cout<<"\nExiting Hospital Management System.\n";
	      cout<<"\nGOOD BYE!\n";
                break;
            }
            default: {
                cout << "\nInvalid choice. Please try again.\n";
                break;
            }
        }
    } while (choice != 0);

    return 0;
}

