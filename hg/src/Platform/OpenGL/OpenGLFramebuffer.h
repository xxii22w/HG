#pragma once

#include "hg/Renderer/Framebuffer.h"

namespace hg {

	class OpenGLFramebuffer : public Framebuffer
	{
	public:
		OpenGLFramebuffer(const FramebufferSpecification& spec);
		virtual ~OpenGLFramebuffer();

		void Invalidate();

		virtual void Bind() override;
		virtual void Unbind() override;

		virtual void Resize(uint32_t width, uint32_t height) override;

		virtual uint32_t GetColorAttachmentRendererID(uint32_t index) const override { HG_CORE_ASSERT(index < m_ColorAttachments.size()); return m_ColorAttachments[index];; }

		virtual const FramebufferSpecification& GetSpecification() const override { return m_Specification; }

	private:
		uint32_t m_RendererID = 0;
		FramebufferSpecification  m_Specification;

		std::vector<FramebufferTextureSpecification> m_ColorAttachmentSpecifications;						// 颜色附件
		FramebufferTextureSpecification m_DepthAttachmentSpecification = FramebufferTextureFormat::None;	// 深度附件

		std::vector<uint32_t> m_ColorAttachments;
		uint32_t m_DepthAttachment = 0;
	};
}