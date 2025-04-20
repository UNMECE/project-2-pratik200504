#include <iostream>
#include <vector>
#include <fstream>
#include <string>

class Student {
protected:
    std::string first_name;
    std::string last_name;
    double gpa;
    int grad_year;
    std::string grad_semester;
    int enrolled_year;
    std::string enrolled_semester;
    std::string level;

public:
    Student() : first_name("N/A"), last_name("N/A"), gpa(0.0), grad_year(0),
                grad_semester("N/A"), enrolled_year(0), enrolled_semester("N/A"), level("N/A") {}

    virtual ~Student() {}

    void setName(std::string first, std::string last) {
        first_name = first;
        last_name = last;
    }

    void setGPA(double g) { gpa = g; }
    void setGradYear(int y) { grad_year = y; }
    void setGradSemester(std::string s) { grad_semester = s; }
    void setEnrolledYear(int y) { enrolled_year = y; }
    void setEnrolledSemester(std::string s) { enrolled_semester = s; }
    void setLevel(std::string l) { level = l; }

    std::string getName() const { return first_name + " " + last_name; }

    virtual void writeInfo(std::ofstream &out) const {
        out << "Name: " << getName() << "\n";
        out << "GPA: " << gpa << "\n";
        out << "Graduation: " << grad_semester << " " << grad_year << "\n";
        out << "Enrolled: " << enrolled_semester << " " << enrolled_year << "\n";
        out << "Level: " << level << "\n";
    }
};

class Art_Student : public Student {
private:
    std::string art_emphasis;

public:
    Art_Student() : art_emphasis("N/A") {}

    void setArtEmphasis(std::string emphasis) { art_emphasis = emphasis; }

    void writeInfo(std::ofstream &out) const override {
        out << "=== Art Student ===\n";
        Student::writeInfo(out);
        out << "Art Emphasis: " << art_emphasis << "\n\n";
    }
};

class Physics_Student : public Student {
private:
    std::string concentration;

public:
    Physics_Student() : concentration("N/A") {}

    void setConcentration(std::string conc) { concentration = conc; }

    void writeInfo(std::ofstream &out) const override {
        out << "=== Physics Student ===\n";
        Student::writeInfo(out);
        out << "Concentration: " << concentration << "\n\n";
    }
};

int main() {
    std::vector<Art_Student *> art_students;
    std::vector<Physics_Student *> physics_students;

    // Art Students - Pratik and friends
    std::string art_first[] = {"Pratik", "Pukar", "Abhinav", "Shriharsh", "Prabin"};
    std::string art_last[]  = {"Ojha", "Adhikari", "", "Acharya", "Loireda"};
    std::string emphases[]  = {"Art Studio", "Art History", "Art Education", "Art Studio", "Art History"};

    for (int i = 0; i < 5; i++) {
        Art_Student *a = new Art_Student();
        a->setName(art_first[i], art_last[i]);
        a->setGPA(3.4 + i * 0.1);
        a->setGradYear(2026 + i);
        a->setGradSemester("Spring");
        a->setEnrolledYear(2022 + i);
        a->setEnrolledSemester("Fall");
        a->setLevel("undergrad");
        a->setArtEmphasis(emphases[i]);
        art_students.push_back(a);
    }

    // Physics Students - Rishav + 4 others
    std::string phys_first[] = {"Rishav", "Lian", "Manoj", "Aarav", "Kriti"};
    std::string phys_last[]  = {"Adhikari", "Regmi", "Poudel", "Sharma", "Lama"};
    std::string concentrations[] = {"Biophysics", "Earth and Planetary Sciences", "Biophysics", "Earth and Planetary Sciences", "Biophysics"};

    for (int i = 0; i < 5; i++) {
        Physics_Student *p = new Physics_Student();
        p->setName(phys_first[i], phys_last[i]);
        p->setGPA(3.6 + i * 0.05);
        p->setGradYear(2025 + i);
        p->setGradSemester("Fall");
        p->setEnrolledYear(2021 + i);
        p->setEnrolledSemester("Spring");
        p->setLevel("grad");
        p->setConcentration(concentrations[i]);
        physics_students.push_back(p);
    }

    std::ofstream outfile("student_info.dat");
    if (!outfile) {
        std::cerr << "Could not open file.\n";
        return 1;
    }

    for (auto a : art_students)
        a->writeInfo(outfile);

    for (auto p : physics_students)
        p->writeInfo(outfile);

    outfile.close();

    for (auto a : art_students) delete a;
    for (auto p : physics_students) delete p;

    return 0;
}

