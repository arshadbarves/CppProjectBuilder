#pragma once

#include <string>
#include <map>

namespace CppProjectBuilder
{
    class ProjectGenerator
    {
    public:
        /// @brief Constructor
        /// @param projectName
        /// @param version
        ProjectGenerator(const std::string &projectName, const std::string &version);

        /// @brief Destructor
        ~ProjectGenerator();

        /// @brief Generate a new project
        void GenerateProject();

    private:
        void LoadTemplates();
        void LoadTemplate(const std::string &templatePath);
        void CreateDirectory(const std::string &path);
        void CreateFile(const std::string &path, const std::string &content);
        std::string ProcessTemplate(const std::string &templateName);
        void ReplaceAll(std::string &str, const std::string &from, const std::string &to);
        void CreateProjectStructure();
        void CreateCMakeLists();
        void CreateSourceFiles();
        void CreateHeaderFiles();
        void CreateTestFiles();
        void CreateGitIgnore();
        void CreateClangFormat();

    private:
        std::string m_projectName;
        std::string m_version;

        std::map<std::string, std::string> m_templates;
    };

} // namespace CppProjectBuilder
