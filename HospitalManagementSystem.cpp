#include <bits/stdc++.h>
using namespace std;

// ----------------------------- Doctor Class -----------------------------
class Doctor {
public:
    string emp_id;
    string name;
    string department;
    int experience;

    Doctor(string id, string n, string dept, int exp) {
        emp_id = id;
        name = n;
        department = dept;
        experience = exp;
    }
};

// ----------------------------- Patient Class -----------------------------
class Patient {
private:
    string P_id;
    string name;
    int age;
    char gender;
    int height;
    float weight;
    int heart_rate;
    string medicalHistory;

public:
    Patient(string id, string n, int a, char g, int h, float w, int hr, string history) {
        P_id = id;
        name = n;
        age = a;
        gender = g;
        height = h;
        weight = w;
        heart_rate = hr;
        medicalHistory = history;
    }

    void GetPatientInfo() {
        cout << "Patient ID: " << P_id << endl;
        cout << "Name: " << name << endl;
        cout << "Age: " << age << endl;
        cout << "Gender: " << gender << endl;
        cout << "Height: " << height << " cm" << endl;
        cout << "Weight: " << weight << " kg" << endl;
        cout << "Heart Rate: " << heart_rate << " bpm" << endl;
        cout << "Medical History: " << medicalHistory << endl;
    }

    string getID() { return P_id; }
};

// ----------------------------- Hospital Class -----------------------------
class Hospital {
private:
    vector<Doctor> doctors;
    vector<Patient> patients;
    map<string, vector<string>> doctorSlots;

public:
    void addDoctor(string id, string name, string dept, int exp) {
        doctors.push_back(Doctor(id, name, dept, exp));
    }

    void addPatient(string p_id, string name, int a, char g, int h, float w, int hr, string history) {
        patients.push_back(Patient(p_id, name, a, g, h, w, hr, history));
    }

    void removeDoctor(string id) {
        for (auto it = doctors.begin(); it != doctors.end(); ++it) {
            if (it->emp_id == id) {
                doctors.erase(it);
                cout << "Doctor removed successfully." << endl;
                return;
            }
        }
        cout << "Doctor not found." << endl;
    }

    void viewDoctors() {
        cout << "-------------------------------------------------------------\n";
        for (auto &doc : doctors) {
            cout << doc.emp_id << "\t" << doc.name << "\t"
                 << doc.department << "\t" << doc.experience << " years\n";
        }
    }

    void displayDoctorByDepartment(const string &department) {
        bool found = false;
        cout << "Doctors in Department: " << department << endl;
        for (auto &doc : doctors) {
            if (doc.department == department) {
                cout << "\t" << doc.emp_id << "\t" << doc.name
                     << "\t" << doc.experience << " years\n";
                found = true;
            }
        }
        if (!found) cout << "No doctors found in this department." << endl;
    }

    void displayPatientById(string id) {
        for (auto &p : patients) {
            if (p.getID() == id) {
                p.GetPatientInfo();
                return;
            }
        }
        cout << "Patient not found." << endl;
    }

    void showSlots(const string &d_id) {
        // Check doctor exists
        bool docExists = false;
        for (auto &doc : doctors) {
            if (doc.emp_id == d_id) {
                docExists = true;
                break;
            }
        }
        if (!docExists) {
            cout << "Invalid Doctor ID." << endl;
            return;
        }

        // Initialize slots if not already
        if (doctorSlots.find(d_id) == doctorSlots.end()) {
            doctorSlots[d_id] = {
                "09:00-09:30", "09:30-10:00", "10:00-10:30", "10:30-11:00",
                "11:00-11:30", "11:30-12:00", "12:00-12:30", "12:30-01:00",
                "02:00-02:30", "02:30-03:00", "03:00-03:30", "03:30-04:00"
            };
        }

        cout << "Available slots for Doctor " << d_id << endl;
        for (size_t i = 0; i < doctorSlots[d_id].size(); ++i) {
            cout << i + 1 << ". " << doctorSlots[d_id][i] << endl;
        }

        cout << "Enter slot number to book: ";
        int slotNum;
        cin >> slotNum;
        if (slotNum >= 1 && slotNum <= (int)doctorSlots[d_id].size()) {
            if (doctorSlots[d_id][slotNum - 1] != "SLOT UNAVAILABLE") {
                doctorSlots[d_id][slotNum - 1] = "SLOT UNAVAILABLE";
                cout << "Slot booked successfully." << endl;
            } else {
                cout << "Slot already booked." << endl;
                showSlots(d_id);
            }
        } else {
            cout << "Invalid slot number." << endl;
        }
    }
};

// ----------------------------- Admin Menu -----------------------------
void AdminMenu(Hospital &h) {
    string password;
    cout << "Enter Admin Password: ";
    cin >> password;

    if (password != "Admin@123") {
        cout << "Incorrect password. Access denied." << endl;
        return;
    }

    cout << "Admin login successful!" << endl;
    int choice;
    while (true) {
        cout << "\n1. Add Doctor\n2. Add Patient\n3. View All Doctors\n4. Remove Doctor\n5. Logout\n";
        cout << "Enter your choice: ";
        cin >> choice;

        if (choice == 1) {
            string id, name, dept;
            int exp;
            cout << "Enter Doctor ID: "; cin >> id;
            cin.ignore();
            cout << "Enter Name: "; getline(cin, name);
            cout << "Enter Department: "; getline(cin, dept);
            cout << "Enter Experience: "; cin >> exp;
            h.addDoctor(id, name, dept, exp);
        } else if (choice == 2) {
            string id, name, history;
            int age, height, hr;
            char gender;
            float weight;

            cout << "Enter Patient ID: "; cin >> id;
            cin.ignore(); // clear newline

            cout << "Enter Name: "; getline(cin, name); // multi-word name

            cout << "Enter Age: "; cin >> age;
            cout << "Enter Gender (M/F): "; cin >> gender;
            cout << "Enter Height (cm): "; cin >> height;
            cout << "Enter Weight (kg): "; cin >> weight;
            cout << "Enter Heart Rate (bpm): "; cin >> hr;
            cin.ignore(); // clear newline

            cout << "Enter Medical History: "; getline(cin, history); // multi-word history

            h.addPatient(id, name, age, gender, height, weight, hr, history);
        } else if (choice == 3) {
            h.viewDoctors();
        } else if (choice == 4) {
            string id;
            cout << "Enter Doctor ID to remove: "; cin >> id;
            h.removeDoctor(id);
        } else if (choice == 5) {
            break;
        } else {
            cout << "Invalid choice. Please try again." << endl;
        }
    }
}

// ----------------------------- Doctor Menu -----------------------------
void DoctorMenu(Hospital &h) {
    cout << "Enter your employee ID: ";
    string doc_id;
    cin >> doc_id;

    if (doc_id.size() == 5 && doc_id.substr(0, 2) == "AH") {
        string last3 = doc_id.substr(2, 3);
        if (last3 >= "001" && last3 <= "021") {
            string password;
            cout << "Enter password: "; cin >> password;
            if (password == "AH@123") {
                cout << "Doctor login successful." << endl;
                cout << "Your Appointments: \n9:00-10:00\t Patient: Alice\t Problem: Fever\n";
            } else {
                cout << "Incorrect password." << endl;
            }
        } else {
            cout << "Invalid employee ID." << endl;
        }
    } else {
        cout << "Invalid employee ID format." << endl;
    }
}

// ----------------------------- Patient Menu -----------------------------
void PatientMenu(Hospital &h) {
    cout << "Enter your patient ID: "; 
    string p_id; cin >> p_id;

    h.displayPatientById(p_id);
    char res;
    cout << "Is this you (y/n)? "; cin >> res;

    if (res == 'y' || res == 'Y') {
        int opt;
        cout << "Select: 1. Book Appointment  2. View Prescription: ";
        cin >> opt;

        if (opt == 1) {
            string issue, department, d_id;
            cout << "Enter your issue: "; cin >> issue;
            cout << "Enter department: "; cin >> department;
            h.displayDoctorByDepartment(department);
            cout << "Enter the Doctor ID you would like to meet: "; cin >> d_id;
            h.showSlots(d_id);
        } else if (opt == 2) {
            h.displayPatientById(p_id);
        }
    }
}

// ----------------------------- Main Function -----------------------------
int main() {
    Hospital h;

    // Add Doctors
    h.addDoctor("AH001", "Alice", "Pediatrics", 5);
    h.addDoctor("AH002", "Bob", "Pediatrics", 8);
    h.addDoctor("AH003", "Charlie", "Orthopedics", 10);
    h.addDoctor("AH004", "David", "Orthopedics", 6);
    h.addDoctor("AH005", "Emma", "General Medicine", 12);
    h.addDoctor("AH006", "Frank", "General Medicine", 7);
    h.addDoctor("AH007", "Grace", "Dermatology", 9);
    h.addDoctor("AH008", "Henrey", "General Surgery", 10);
    h.addDoctor("AH009", "Jack", "Cardiology", 10);
    h.addDoctor("AH010", "Kate", "Pediatrics", 4);
    h.addDoctor("AH011", "Liam", "Pediatrics", 11);
    h.addDoctor("AH012", "Mia", "Orthopedics", 15);
    h.addDoctor("AH013", "Noah", "Orthopedics", 3);
    h.addDoctor("AH014", "Olivia", "General Medicine", 9);
    h.addDoctor("AH015", "Peter", "General Medicine", 14);
    h.addDoctor("AH016", "Quinn", "Dermatology", 5);
    h.addDoctor("AH017", "Riley", "Dermatology", 12);
    h.addDoctor("AH018", "Sophia", "General Surgery", 8);
    h.addDoctor("AH019", "Tom", "General Surgery", 16);
    h.addDoctor("AH020", "Uma", "Cardiology", 7);
    h.addDoctor("AH021", "Victor", "Cardiology", 13);

    // Add Patients
    h.addPatient("PT001", "Aaron", 35, 'M', 180, 82.5, 72, "Fractured arm in 2020");
    h.addPatient("PT002", "Bella", 28, 'F', 162, 58.0, 68, "Migraines, Penicillin allergy");
    h.addPatient("PT003", "Caleb", 45, 'M', 175, 88.3, 80, "High cholesterol, Hypertension");
    h.addPatient("PT004", "Daisy", 68, 'F', 155, 65.1, 85, "Type 2 Diabetes, Arthritis");
    h.addPatient("PT005", "Ethan", 52, 'M', 178, 79.0, 75, "Asthma");
    h.addPatient("PT006", "Fiona", 22, 'F', 168, 61.2, 65, "None");
    h.addPatient("PT007", "George", 75, 'M', 170, 75.5, 90, "Heart surgery in 2018");
    h.addPatient("PT008", "Hannah", 31, 'F', 160, 55.7, 70, "Anemia");
    h.addPatient("PT009", "Isaac", 49, 'M', 182, 95.0, 82, "Sleep Apnea");
    h.addPatient("PT010", "Julia", 60, 'F', 158, 72.8, 78, "Osteoporosis, High BP");

    // Main Menu
    while (true) {
        int choice;
        cout << "\n\t\t-----------------WELCOME TO THE AH MANAGEMENT SYSTEM------------------------\n";
        cout << "Enter your login status: \n1. Admin\n2. Doctor\n3. Patient\n4. Exit\n";
        cin >> choice;

        if (choice == 1) AdminMenu(h);
        else if (choice == 2) DoctorMenu(h);
        else if (choice == 3) PatientMenu(h);
        else if (choice == 4) break;
        else cout << "Invalid Choice." << endl;
    }

    return 0;
}
