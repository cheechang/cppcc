#pragma once
#include <vector>
#include <algorithm>
#include <Defines.h>
namespace ui{
	template <typename T>
	class PageSizeDataItem{
	public:
		PageSizeDataItem():m_totalPage(0),m_pageSize(0),m_currentPage(0),m_size(0){
		};
		virtual ~PageSizeDataItem(){};
		bool isLoadFinished(){
			return (m_currentPage==m_totalPage);
		}
		void setData(std::vector<T>&data){
			m_data = data;
			m_totalPage = m_data.size()/m_pageSize+(data.size()%m_pageSize>0?1:0);
		}
		void setReverseData(std::vector<T>&data){
			m_data = data;
			std::reverse(m_data.begin(),m_data.end());
			m_totalPage = m_data.size()/m_pageSize+(data.size()%m_pageSize>0?1:0);
		}
		void setPageSize(const int32 pageSize){
			m_pageSize=pageSize;
		};
		int32 getPageSize()const{
			return m_pageSize;
		};
		int32 getDataCount()const{
			return m_data.size();
		};
		void clearData(){
			m_data.clear();
			m_currentPage =0;
			m_totalPage = 0;
		};
		void getPageData(std::vector<T>&data){
			if(m_data.empty()) return;
			//只有一页数据
			if(m_pageSize>=m_data.size()){
				data.assign(m_data.begin(),m_data.end());
			}
			else{
				if((m_currentPage+1) == m_totalPage && (m_data.size()%m_pageSize)){
					data.assign(m_data.begin()+m_currentPage*m_pageSize,m_data.end());
				}
				else{
					data.assign(m_data.begin()+m_currentPage*m_pageSize,(m_data.begin()+(m_currentPage+1)*m_pageSize));
				}
			}
			++m_currentPage;

			//判断是否加载完毕,只有页数据的情况
			if(isLoadFinished()){
				clearData();
			}
		}

		void getAllPageData(std::vector<T>&data){
			if(m_data.empty()) return;
			//获取全部数据
			data.assign(m_data.begin(),m_data.end());
		}
	private:
		int32   m_size;
		int32	m_totalPage;
		int32	m_pageSize;
		int32	m_currentPage;
		std::vector<T> m_data;
	};
}