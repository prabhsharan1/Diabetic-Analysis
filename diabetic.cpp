#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <algorithm>

class DiagnosisSystem {
public:
    virtual void diagnose() const = 0;
};

class HeartAttackDiagnosis : public DiagnosisSystem {
public:
    void diagnose() const override {
        std::cout << "Diagnosing heart attack based on symptoms..." << std::endl;
        // Simple simulation of heart attack diagnosis logic
        std::cout << "Checking for chest pain, shortness of breath, and sweating..." << std::endl;
        // Add further logic as needed
    }
};

class StrokeDiagnosis : public DiagnosisSystem {
public:
    void diagnose() const override {
        std::cout << "Diagnosing stroke based on symptoms..." << std::endl;
        // Simple simulation of stroke diagnosis logic
        std::cout << "Checking for slurred speech, arm weakness, and face drooping..." << std::endl;
        // Add further logic as needed
    }
};

class Patient {
private:
    std::string name;
    int age;
    std::vector<std::shared_ptr<DiagnosisSystem>> diagnoses;

public:
    Patient(std::string patientName, int patientAge)
        : name(std::move(patientName)), age(patientAge) {}

    void addDiagnosis(std::shared_ptr<DiagnosisSystem> diagnosis) {
        diagnoses.push_back(diagnosis);
    }

    void performDiagnoses() const {
        std::cout << "Performing diagnoses for " << name << " (Age: " << age << ")\n";
        for (const auto& diagnosis : diagnoses) {
            diagnosis->diagnose();
        }
    }

    void displayPatientInfo() const {
        std::cout << "Patient: " << name << ", Age: " << age << std::endl;
    }
};

class DiagnosisManager {
private:
    std::vector<std::shared_ptr<DiagnosisSystem>> availableDiagnoses;

public:
    DiagnosisManager() {
        // Add initial diagnoses
        availableDiagnoses.push_back(std::make_shared<HeartAttackDiagnosis>());
        availableDiagnoses.push_back(std::make_shared<StrokeDiagnosis>());
    }

    void showAvailableDiagnoses() const {
        std::cout << "Available diagnoses:\n";
        for (size_t i = 0; i < availableDiagnoses.size(); ++i) {
            std::cout << i + 1 << ". ";
            availableDiagnoses[i]->diagnose();
        }
    }

    void selectDiagnosis(int diagnosisIndex, Patient& patient) const {
        if (diagnosisIndex > 0 && diagnosisIndex <= availableDiagnoses.size()) {
            patient.addDiagnosis(availableDiagnoses[diagnosisIndex - 1]);
            std::cout << "Diagnosis added to patient.\n";
        } else {
            std::cout << "Invalid diagnosis selection.\n";
        }
    }
};

int main() {
    // Create a patient instance
    Patient patient("John Doe", 45);

    // Display available diagnoses
    DiagnosisManager manager;
    manager.showAvailableDiagnoses();

    // Allow user to select a diagnosis
    int selection;
    std::cout << "Select a diagnosis (1/2): ";
    std::cin >> selection;

    // Add selected diagnosis to the patient
    manager.selectDiagnosis(selection, patient);

    // Display patient info and perform diagnosis
    patient.displayPatientInfo();
    patient.performDiagnoses();

    return 0;
}
