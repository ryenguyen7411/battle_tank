#pragma once

namespace stdio_fw
{
	class AffineTransform
	{
		Mat3	m_matR, m_matT, m_matS;
		Mat3	m_matTrans;

		int		m_tX, m_tY;
		float	m_alpha;
		float	m_sX, m_sY;

	public:
		AffineTransform();
		~AffineTransform();

		int		getTranslateX();
		int		getTranslateY();
		void	translate(int x, int y);
				
		void	rotate(float alpha);
		void	rotate(float alpha, int anchorX, int anchorY);

		float	getScaleX();
		float	getScaleY();
		void	scale(float sx, float sy);

		void		setTransform(const Mat3& mat);
		const Mat3&	getMatrix();

		void	resetTransform();

	private:
		void	updateTransformMatrix();
	};
}

