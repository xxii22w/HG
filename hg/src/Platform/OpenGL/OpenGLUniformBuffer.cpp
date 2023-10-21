#include "hgpch.h"
#include "OpenGLUniformBuffer.h"

#include <glad/glad.h>

namespace hg {

	OpenGLUniformBuffer::OpenGLUniformBuffer(uint32_t size, uint32_t binding)
	{
		glCreateBuffers(1, &m_RendererID);
		glNamedBufferData(m_RendererID, size, nullptr, GL_DYNAMIC_DRAW); // TODO: 创建并初始化缓冲区对象的数据存储
		glBindBufferBase(GL_UNIFORM_BUFFER, binding, m_RendererID);		 // 将缓冲区对象绑定到索引缓冲区目标
	}

	OpenGLUniformBuffer::~OpenGLUniformBuffer()
	{
		glDeleteBuffers(1, &m_RendererID);
	}


	void OpenGLUniformBuffer::SetData(const void* data, uint32_t size, uint32_t offset)
	{
		glNamedBufferSubData(m_RendererID, offset, size, data);		// 更新缓冲区对象数据存储的子集
	}

}