#include"StuManage.h"

/*-------------------------------学生工具组--------------------------------*/

// 按照课程编号选课
/*
*/
bool StudentModuleTools::SelectCourse(CourseData& cData, StudentCourseData& scData, const Student& user,std::string courseNumTemp)
{
	for (size_t i = 0; i < cData.data.size(); i++)
	{
		// 查找该课程编号
		if (cData.data[i].GetCourseNum() == courseNumTemp)
		{
			// 验证该课程是否已满
			if(!cData.data[i].isFull())
			{ 
				// 查找到该用户的学生选课数据
				StudentCourse* user_sc = NULL;
				for (size_t c = 0; c < scData.data.size(); c++)
				{
					if (scData.data[c].GetID() == user.GetID())
					{
						// 如果找到了，添加引用
						user_sc = &(scData.data[c]);
					}
				}
				// 如果没有重复
                cData.data[i].AddOnePopulation();
                // 将学生选课的总选课数加一
                user_sc->AddOneSeletedCourseNum();
                // 在学生课程数据中添加该选课信息
                user_sc->selectedCourses.push_back(cData.data[i]);
                return 0;

			}
			else
			{
                return true;
			}
		}
	}
    return true;
}
bool StudentModuleTools::DeleteCourse(CourseData& cData, StudentCourseData& scData, const Student& user,std::string courseNumTemp)
{
    for (size_t i = 0; i < cData.data.size(); i++)
    {
        // 查找该课程编号
        if (cData.data[i].GetCourseNum() == courseNumTemp)
        {
                // 查找到该用户的学生选课数据
                StudentCourse* user_sc = NULL;
                for (size_t c = 0; c < scData.data.size(); c++)
                {
                    if (scData.data[c].GetID() == user.GetID())
                    {
                        // 如果找到了，添加引用
                        user_sc = &(scData.data[c]);
                    }
                }
                // 如果没有重复

                // 将学生选课的总选课数减一

                // 在学生课程数据中添加该选课信息

                for (size_t j = 0; j < user_sc->selectedCourses.size(); j++)
                {
                    if(user_sc->selectedCourses[j].GetCourseNum() == courseNumTemp) {
                        user_sc->selectedCourses.erase(user_sc->selectedCourses.begin()+j);
                        user_sc->MinusOneSeletedCourseNum();
                        cData.data[i].MinusOnePopulation();
                        return 0;
                    }
                }

        }
    }
    return true;
}

// 删除学生信息

bool ManagerModuleTools::Manage_Delete_nonecourse(StudentData& sData, StudentCourseData& scData, CourseData& cData,std::string stuID)
{
    while (true)
    {

        bool is_stu_success = false;
        bool is_sc_success = false;

        for (size_t i = 0; i < sData.data.size(); i++)
        {
            if (sData.data[i].GetID() == stuID)
            {
                // 删除学生数据
                auto iter = sData.data.begin() + i;
                sData.data.erase(iter);
                is_stu_success = true;
                break;
            }
        }
        if (is_stu_success)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
}

bool ManagerModuleTools::Manage_Delete(StudentData& sData, StudentCourseData& scData, CourseData& cData,std::string stuID)
{
    while (true)
    {

        bool is_stu_success = false;
        bool is_sc_success = false;

        for (size_t i = 0; i < sData.data.size(); i++)
        {
            if (sData.data[i].GetID() == stuID)
            {
                // 删除学生数据
                auto iter = sData.data.begin() + i;
                sData.data.erase(iter);
                is_stu_success = true;
                break;
            }
        }
        for (size_t i = 0; i < scData.data.size(); i++)
        {
            if (scData.data[i].GetID() == stuID)
            {
                // 存储课号
                std::vector<std::string> courseNums;
                // 删除之前修改他已选课程的选课人数数据
                for (int c = 0; c < scData.data[i].GetSelectedCourseNum(); c++)
                {
                    //拿到所有已选课的课号
                    courseNums.push_back(scData.data[i].selectedCourses[c].GetCourseNum());
                }
                for (size_t r = 0; r < courseNums.size(); r++)
                {
                    // 将课程的已选人数减一
                    for (size_t d = 0; d < cData.data.size(); d++)
                    {
                        if (courseNums[r] == cData.data[d].GetCourseNum())
                        {
                            cData.data[d].MinusOnePopulation();
                            break;
                        }
                    }
                }

                // 删除学生选课数据
                auto iter = scData.data.begin() + i;
                scData.data.erase(iter);
                is_sc_success = true;
                break;
            }
        }

        if (is_stu_success && is_sc_success)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
}
void ManagerModuleTools::Manage_Delete(CourseData& cData, StudentCourseData& scData,std::string courseNum)
{
	// 删除所有学生选课中本课程的记录
	for (size_t i = 0; i < scData.data.size(); i++)
	{
		// 如果该学生选了课
		if (scData.data[i].GetSelectedCourseNum() > 0)
		{
			// 查找其中是否有该课程
			for (size_t c = 0; c < scData.data[i].selectedCourses.size(); c++)
			{
				// 如果有，删除选课记录
				if (courseNum == scData.data[i].selectedCourses[c].GetCourseNum())
				{
					auto iter = scData.data[i].selectedCourses.begin() + c;
					scData.data[i].selectedCourses.erase(iter);
					scData.data[i].MinusOneSeletedCourseNum();
					break;
				}
			}
		}
	}
	// 在课程数据容器中找到该课程
	for (size_t i = 0; i < cData.data.size(); i++)
	{
		if (courseNum == cData.data[i].GetCourseNum())
		{
			// 删除它
			auto iter = cData.data.begin() + i;
			cData.data.erase(iter);
			break;
		}
	}
}
// 学生登录模块
bool StudentRegister_check(const StudentData & data,std::string stuID,std::string password)
{
    const Student* temp;

    // 查找该学生
    temp = FindStudent(stuID, data);
    if(temp == NULL) return false;
    if (Verification(*temp, password)){
        return true;
    }
    else{
        return false;
    }


}
const Student* StudentRegister_getInfo(const StudentData & data,std::string stuID)
{
	const Student* temp;
	// 查找该学生
    temp = FindStudent(stuID, data);
	return temp;
}
// 管理员登录模块
const Manager* ManagerRegister(const ManagerData& data,std::string name,std:: string pwd)
{
	const Manager* temp;
    temp = FindManager(data,name);
    if(temp == NULL) return NULL;
    if (Verification(*temp, pwd))
    {
        return temp;
    }
    else
    {
        return NULL;
    }
}
/*
*/
// 验证学生密码
bool Verification(const Student & user, const std::string password)
{
	if (user.GetPassword() == password)
	{
		return true;
	}
	else
	{
		return false;
	}
}
/**/
// 验证管理员密码
bool Verification(const Manager& data, const std::string password)
{
    if(data.GetPassword() == password) return true;
	return false;
}
/*
// 查找学生是否存在
*/
const Student* FindStudent(const std::string temp, const StudentData& data)
{
	// 用于返回值
	const Student* stemp = NULL;
	while (true)
	{
		bool is_find = false;
		auto end = data.data.end();
		for (auto i = data.data.begin(); i < end; i++)
		{
			if (i->GetID() == temp)
			{
				stemp = &(*i);
				is_find = true;
				break;
			}
		}
		if (is_find)
		{
			return stemp;
		}
		else
		{
            return NULL;
		}
	}
}
/**/
// 查找管理员是否存在
const Manager* FindManager(const ManagerData& data,std::string name)
{
	const Manager* mtemp = NULL;
	while (true)
	{
		bool is_find = false;
		auto end = data.data.end();
		for (auto i = data.data.begin(); i < end; i++)
		{
            if (i->GetName() == name)
			{
				mtemp = &(*i);
				is_find = true;
				break;
			}
		}
		if (is_find)
		{
			return mtemp;
		}
		else
		{
            return NULL;
        }
	}

}
