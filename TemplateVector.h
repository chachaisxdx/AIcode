#pragma once

#ifndef P3D_P3DGEOMOBGECT_TEMPLATEVECTOR_H
#define P3D_P3DGEOMOBGECT_TEMPLATEVECTOR_H

namespace P3D_NAMESPACE_NAME
{
	
	template <typename T>
    class TemplateVector : public pvector <T>
	{
	protected:
		uint32_t m_numPerStruct;
		uint32_t m_structsPerRow;
		uint32_t m_tag;
		uint32_t m_indexFamily;
		uint32_t m_indexedBy;
		bool     m_active;
	public:
		P3DGEOMOBJECT_EXPORT TemplateVector(uint32_t numPerStruct,
			uint32_t structsPerRow = 0, uint32_t tag = 0, uint32_t indexFamily = 0, uint32_t indexedBy = 0, bool active = false);
		P3DGEOMOBJECT_EXPORT TemplateVector();

	public:
		P3DGEOMOBJECT_EXPORT uint32_t numPerStruct() const;
		P3DGEOMOBJECT_EXPORT uint32_t structsPerRow() const;
		P3DGEOMOBJECT_EXPORT void   setStructsPerRow(uint32_t num);
		P3DGEOMOBJECT_EXPORT uint32_t getTag() const;
		P3DGEOMOBJECT_EXPORT uint32_t getIndexFamily() const;
		P3DGEOMOBJECT_EXPORT uint32_t getIndexedBy() const;
		P3DGEOMOBJECT_EXPORT void setTags(uint32_t numPeStruct, uint32_t structsPerRow, uint32_t tag, uint32_t getIndexFamily, uint32_t getIndexedBy, bool active);
		P3DGEOMOBJECT_EXPORT void copyVectorFrom(pvector<T>&source);

		P3DGEOMOBJECT_EXPORT uint32_t clearAndAppendBlock(TemplateVector<T> &source, uint32_t i0, uint32_t numWrap, uint32_t n);
		P3DGEOMOBJECT_EXPORT uint32_t clearAndAppendBlock(T const *source, size_t sourceSize, uint32_t i0, uint32_t numWrap, uint32_t n);

		P3DGEOMOBJECT_EXPORT uint32_t clearAndAppendByOneBasedIndices
			(
			pvector<int> &zeroBasedIndices,
			pvector<bool> *positive,
			pvector<T> &source,
			pvector<int> &oneBasedIndices,
			uint32_t i0,
			uint32_t numItem,
			uint32_t numWrap
			);

		P3DGEOMOBJECT_EXPORT uint32_t clearAndAppendByOneBasedIndices
			(
			pvector<int> &zeroBasedIndices,
			pvector<bool> *positive,
			T const *pSource,
			size_t sourceCount,
			int const *oneBasedIndices,
			size_t oneBasedIndexCount,
			uint32_t i0,
			uint32_t numItem,
			uint32_t numWrap
			);
        
		P3DGEOMOBJECT_EXPORT size_t appendAndReturnIndex(T const &source);
		P3DGEOMOBJECT_EXPORT size_t numCompleteRows();
		P3DGEOMOBJECT_EXPORT void reverseInRange(size_t iFirst, size_t iLast);
        P3DGEOMOBJECT_EXPORT bool tryGetAt(size_t index, T const &defaultValue, T &value) const;

        P3DGEOMOBJECT_EXPORT bool isActive() const;
        P3DGEOMOBJECT_EXPORT void setActive(bool active);
        P3DGEOMOBJECT_EXPORT size_t append(T const *pBuffer,size_t count);
        P3DGEOMOBJECT_EXPORT size_t append(TemplateVector<T> const &source);
        P3DGEOMOBJECT_EXPORT size_t append(T const &source);
        P3DGEOMOBJECT_EXPORT T* getPtr();
        P3DGEOMOBJECT_EXPORT T const * getCP() const;
        P3DGEOMOBJECT_EXPORT void copyData(size_t fromIndex, size_t toIndex);
        P3DGEOMOBJECT_EXPORT void trim(size_t index0, size_t count);
	};

    class TemplateVectorInt : public TemplateVector<int>
	{
    public:
		TemplateVectorInt() : TemplateVector<int>() {}

		TemplateVectorInt(uint32_t numPerStruct,
			uint32_t structsPerRow = 0, uint32_t tag = 0, uint32_t indexFamily = 0, uint32_t indexedBy = 0, bool active = false)
			: TemplateVector<int>(numPerStruct, structsPerRow, tag, indexFamily, indexedBy, active)
		{}

        P3DGEOMOBJECT_EXPORT void absAll();

		P3DGEOMOBJECT_EXPORT void convertBlockedToZeroTerminated();
		P3DGEOMOBJECT_EXPORT size_t countZeros();
		P3DGEOMOBJECT_EXPORT void addTerminatedSequentialBlocks
			(
			size_t numRow,
			size_t numPerRow,
			bool clearFirst = false,
			int firstValue = 1,
			int terminator = 0
			);
		P3DGEOMOBJECT_EXPORT void addSequentialBlock
			(
			int firstValue,
			size_t numValue,
			size_t numWrap,
			size_t numTrailingZero = 0,
			bool clearFirst = false
			);
		P3DGEOMOBJECT_EXPORT bool addAndTerminate
			(
			int *pValues,
			size_t numValues
			);
		P3DGEOMOBJECT_EXPORT void addTerminatedGridBlocks
			(
			size_t numRow,
			size_t numPerRow,
			size_t rowStep,
			size_t colStep,
			bool triangulated,
			bool clearFirst,
			int firstValue,
			int terminator);
		P3DGEOMOBJECT_EXPORT void negateInRange(size_t iFirst, size_t iLast);

		P3DGEOMOBJECT_EXPORT void shiftSignsFromCyclicPredecessorsInRange(size_t kFirst, size_t kLast);

		P3DGEOMOBJECT_EXPORT void absInRange(size_t iFirst, size_t iLast);

		P3DGEOMOBJECT_EXPORT bool allNegativeInRange(size_t iFirst, size_t iLast);

		P3DGEOMOBJECT_EXPORT void negativeAbsInRange(size_t iFirst, size_t iLast);

		P3DGEOMOBJECT_EXPORT bool delimitFace(int numPerFace, size_t iFirst, size_t &iLast, size_t &iNext);

		P3DGEOMOBJECT_EXPORT bool getMinMax(int &minValue, int &maxValue) const;

		P3DGEOMOBJECT_EXPORT void appendShifted(TemplateVectorInt const & source, int shift);

        enum IndexAction
		{
			None,
			ForcePositive,
			ForceNegative,
			Negate
		};
	};
	

	typedef TemplateVector<GePoint3d>&            TemplateVectorGePoint3dR;
	typedef TemplateVector<GePoint3d> const &     TemplateVectorGePoint3dCR;
	typedef TemplateVector<GePoint3d> const *     TemplateVectorGePoint3dCP;

	typedef TemplateVector<GePoint2d>&            TemplateVectorGePoint2dR;
	typedef TemplateVector<GePoint2d> const&      TemplateVectorGePoint2dCR;
	typedef TemplateVector<GePoint2d>*            TemplateVectorGePoint2dP;
	typedef TemplateVector<GePoint2d> const *     TemplateVectorGePoint2dCP;

	typedef TemplateVector<GeVec3d>&              TemplateVectorGeVec3dR;
	typedef TemplateVector<GeVec3d> const&        TemplateVectorGeVec3dCR;
	typedef TemplateVector<GeVec3d>*              TemplateVectorGeVec3dP;
	typedef TemplateVector<GeVec3d> const*        TemplateVectorGeVec3dCP;

	typedef TemplateVectorInt&                    TemplateVectorIntR;
	typedef TemplateVectorInt const&              TemplateVectorIntCR;
	typedef TemplateVectorInt*                    TemplateVectorIntP;
	typedef TemplateVectorInt const*              TemplateVectorIntCP;

	typedef TemplateVector<uint32_t>&             TemplateVectorUInt32R;
	typedef TemplateVector<uint32_t> const&       TemplateVectorUInt32CR;
	typedef TemplateVector<uint32_t>*             TemplateVectorUInt32P;
	typedef TemplateVector<uint32_t> const*       TemplateVectorUInt32CP;

	typedef TemplateVector<double>&               TemplateVectorDoubledR;
	typedef TemplateVector<double> const&         TemplateVectorDoubledCR;
	typedef TemplateVector<double>   *            TemplateVectorDoubledP;
	typedef TemplateVector<double> const*         TemplateVectorDoubledCP;
                                                 
    typedef TemplateVector<RgbFactor>& TemplateVectorRgbFactorR;
    typedef TemplateVector<RgbFactor> const& TemplateVectorRgbFactorCR;
    typedef TemplateVector<RgbFactor>* TemplateVectorRgbFactorP;
    typedef TemplateVector<RgbFactor> const* TemplateVectorRgbFactorCP;
    typedef TemplateVector<FloatRgb>& TemplateVectorRgbFloatR;

	typedef TemplateVector<GeCurveTopologyId>&      TemplateVectorCurveTopologyIdR;

}


#endif