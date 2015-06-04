#include "stdio_fw.h"
#include "Utils\AffineTransform.h"

namespace stdio_fw
{
	AffineTransform::AffineTransform()
	{
		resetTransform();
	}

	AffineTransform::~AffineTransform()
	{

	}

	int	AffineTransform::getTranslateX()
	{
		return m_tX;
	}

	int	AffineTransform::getTranslateY()
	{
		return m_tY;
	}

	void AffineTransform::translate(int x, int y)
	{
		m_tX = x;
		m_tY = y;
		m_matT.setTranslation(m_tX, m_tY);
		updateTransformMatrix();
	}

	void AffineTransform::rotate(float alpha)
	{
		m_matR.setRotation(alpha);
		updateTransformMatrix();
	}

	void AffineTransform::rotate(float alpha, int anchorX, int anchorY)
	{
		Mat3 mT1, mT2, mR;
		mT1.setTranslation(-(anchorX - m_tX), -(anchorY - m_tY));
		mR.setRotation(alpha);
		mT2.setTranslation(anchorX - m_tX, anchorY - m_tY);

		m_matR = mT1 * mR * mT2;
		updateTransformMatrix();
	}

	float AffineTransform::getScaleX()
	{
		return m_sX;
	}

	float AffineTransform::getScaleY()
	{
		return m_sY;
	}

	void AffineTransform::scale(float sx, float sy)
	{
		m_sX = sx;
		m_sY = sy;
		m_matS.setScale(m_sX, m_sY);
		updateTransformMatrix();
	}

	void AffineTransform::setTransform(const Mat3& mat)
	{
		m_matTrans = mat;
	}

	const Mat3&	AffineTransform::getMatrix()
	{
		return m_matTrans;
	}

	void AffineTransform::updateTransformMatrix()
	{
		m_matTrans = m_matS * m_matR * m_matT;
	}

	void AffineTransform::resetTransform()
	{
		m_tX = m_tY = 0;		 
		m_alpha = 0.0f;
		m_sX = m_sY = 1.0f;		 
		
		m_matR.setIdentity();
		m_matT.setIdentity();
		m_matS.setIdentity();
		m_matTrans.setIdentity();
	}
}
