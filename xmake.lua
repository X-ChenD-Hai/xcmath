add_rules("mode.debug","mode.release")
add_requires("gtest","glm")
set_project("xcmath")
set_version("1.0.0")
set_languages("c++23")
target("xcmath")
    set_kind("phony")
    add_includedirs(".",{ public=true })

for _,file in ipairs(os.files("tests/*.cc")) do
    target(file:gsub("%.cc","").."_test")
        set_kind("binary")
        add_files(file)
        add_deps("xcmath")
        add_packages("gtest", "glm")
end