
#include "ProjectGenerator.h"
#include <fstream>

namespace CppProjectBuilder
{
    ProjectGenerator::ProjectGenerator(const std::string &projectName, const std::string &version) : m_projectName(projectName), m_version(version)
    {
        LoadTemplates();
    }

    ProjectGenerator::~ProjectGenerator()
    {
    }

    void ProjectGenerator::GenerateProject()
    {
        CreateProjectStructure();
        CreateCMakeLists();
        CreateSourceFiles();
        CreateHeaderFiles();
        CreateTestFiles();
    }

    void ProjectGenerator::LoadTemplates()
    {
        LoadTemplate("templates/CMakeLists.txt.template");
        LoadTemplate("templates/clang-format.template");
        LoadTemplate("templates/gitignore.template");
        LoadTemplate("templates/main.cpp.template");
    }

    void ProjectGenerator::LoadTemplate(const std::string &templatePath)
    {
        std::ifstream file(templatePath);

        if (!file)
        {
            throw std::runtime_error("Failed to open the template file: " + templatePath);
        }

        // Read the content of the file
        m_templates[templatePath] = std::string((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
    }

    void ProjectGenerator::CreateDirectory(const std::string &path)
    {
        if (!std::filesystem::create_directory(path))
        {
            throw std::runtime_error("Failed to create directory: " + path);
        }
    }

    void ProjectGenerator::CreateFile(const std::string &path, const std::string &content)
    {
        std::ofstream file(path);

        if (!file)
        {
            throw std::runtime_error("Failed to create file: " + path);
        }

        file << content;
    }

    std::string ProjectGenerator::ProcessTemplate(const std::string &templateName)
    {
        std::string content = m_templates[templateName];
        ReplaceAll(content, "{{PROJECT_NAME}}", m_projectName);
        ReplaceAll(content, "{{PROJECT_VERSION}}", m_version);

        return content;
    }

    void ProjectGenerator::ReplaceAll(std::string &str, const std::string &from, const std::string &to)
    {
        size_t start_pos = 0;
        while ((start_pos = str.find(from, start_pos)) != std::string::npos)
        {
            str.replace(start_pos, from.length(), to);
            start_pos += to.length();
        }
    }

    void ProjectGenerator::CreateProjectStructure()
    {
        CreateDirectory(m_projectName);
        CreateDirectory(m_projectName + "/src");
        CreateDirectory(m_projectName + "/include");
        CreateDirectory(m_projectName + "/test");
    }

    void ProjectGenerator::CreateCMakeLists()
    {
        std::string content = ProcessTemplate("templates/CMakeLists.txt.template");
        CreateFile(m_projectName + "/CMakeLists.txt", content);
    }

    void ProjectGenerator::CreateSourceFiles()
    {
        std::string content = ProcessTemplate("templates/main.cpp.template");
        CreateFile(m_projectName + "/src/main.cpp", content);
    }

    void ProjectGenerator::CreateHeaderFiles()
    {
        // Create a header file
        std::string headerContent = "#pragma once\n\n";
        CreateFile(m_projectName + "/include/" + m_projectName + ".h", headerContent);
    }

    void ProjectGenerator::CreateTestFiles()
    {
        // Create a test file
        std::string testContent = "#include <gtest/gtest.h>\n\n";
        testContent += "TEST(" + m_projectName + ", Test1)\n";
        testContent += "{\n";
        testContent += "    EXPECT_EQ(1, 1);\n";
        testContent += "}\n";
        CreateFile(m_projectName + "/test/" + m_projectName + "Test.cpp", testContent);
    }

    void ProjectGenerator::CreateGitIgnore()
    {
        std::string content = ProcessTemplate("templates/gitignore.template");
        CreateFile(m_projectName + "/.gitignore", content);
    }

    void ProjectGenerator::CreateClangFormat()
    {
        std::string content = ProcessTemplate("templates/clang-format.template");
        CreateFile(m_projectName + "/.clang-format", content);
    }
}
