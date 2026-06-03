
/**
@brief     包含二维点类GePoint3d的成员变量和接口函数
@file      GePoint3d.h
@author    北京构力科技有限公司
@date      2021-07-26
@copyright Copyright (C), 2019-2028, Beijing Glory PKPM Technology. Co., Ltd.
*/
#pragma once

#ifndef P3D_P3DGEOMBASE_GEPOINT3D_H
#define P3D_P3DGEOMBASE_GEPOINT3D_H

namespace P3D_NAMESPACE_NAME {

	/**
	@brief     三维点的类，包含三维点的成员变量和接口函数
	*/
	class P3DGEOMBASE_EXPORT GePoint3d
	{
	public:
		double x;
		double y;
		double z;

	public:
		/**
		*@brief 判断数值成员变量是否为有效数值
		*@return true有效，false存在无效数值的成员变量
		 
		*/
		bool isValidNum() const;

		/**
		 *@brief 返回一个与该点原点对称的点
		 *@return GePoint3d，一个新的三维点
		 *@note 原三维点没有发生变化
		*/
		GePoint3d operator-() const;
		/**
		 *@brief 返回该点与一个三维向量对应坐标相加的结果
		 *@param vec：GeVec3dCR，一个三维向量的常量引用
		 *@return GePoint3d，一个新的三维点
		 *@note 原三维点和向量没有发生变化
		*/
		GePoint3d operator+(GeVec3dCR vec) const;
		/**
		 *@brief 该点与一个三维向量对应坐标相加的结果
		 *@param vec：GeVec3dCR，一个三维向量的常量引用
		 *@return GePoint3dR，该点
		 *@note 该点坐标可能变化
		*/
		GePoint3dR operator+=(GeVec3dCR vec);
		/**
		 *@brief 返回该点与一个三维向量对应坐标相减的结果
		 *@param vec：GeVec3dCR，一个三维向量的常量引用
		 *@return GePoint3d，一个新的三维点
		 *@note 原三维点和向量没有发生变化
		*/
		GePoint3d operator-(GeVec3dCR vec) const;
		/**
		 *@brief 该点与一个三维向量对应坐标相减的结果
		 *@param vec：GeVec3dCR，一个三维向量的常量引用
		 *@return GeVec3dCR，该点
		 *@note 该点坐标可能变化
		*/
		GePoint3dR operator-=(GeVec3dCR vec);

		/**
		 *@brief 返回该点与一个三维点对应坐标相加的结果
		 *@param point：GePoint3dCR，一个三维点的常量引用
		 *@return GePoint3d，一个新的三维点
		 *@note 原三维点都没有发生变化
		*/
		GePoint3d operator+(GePoint3dCR point) const;
		/**
		 *@brief 返回以该点为终点point为起点的向量
		 *@param point：GePoint3dCR，一个三维点的常量引用
		 *@return GeVec3d，以该点为终点point为起点的向量
		 *@note 原三维点都没有发生变化
		*/
		GeVec3d operator-(GePoint3dCR point) const;

		/**
		 *@brief 返回该点与一个标量相乘的结果
		 *@param scale：double，标量
		 *@return GePoint3d，一个新的三维点
		 *@note 原三维点没有发生变化
		*/
		GePoint3d operator*(double scale) const;
		/**
		 *@brief 返回该点与一个标量相乘的结果
		 *@param scale：double，标量
		 *@return GePoint3dR，该点
		 *@note 该点可能发生变化
		*/
		GePoint3dR operator*=(double scale);

		/**
		 *@brief 返回该点与一个三维点的点积
		 *@param point：GePoint3dCR，一个三维点的常量引用
		 *@return double，点积的结果
		  
		*/
		double operator*(GePoint3dCR point) const;
		/**
		 *@brief 返回该点与一个三维向量的点积
		 *@param vec：GeVec3dCR，一个三维向量的常量引用
		 *@return double，点积的结果
		  
		*/
		double operator*(GeVec3dCR vec) const;
		/**
		 *@brief 返回以原点为起点该点和point为终点的向量的叉积
		 *@param point：GePoint3dCR，一个三维点的常量引用
		 *@return GeVec3d，原点为起点 该点 和 point 为终点的向量的叉积
		  
		*/
		GeVec3d operator^(GePoint3dCR point) const;
		/**
		 *@brief 返回以原点为起点该点为终点的向量与一个三维向量的叉积
		 *@param vec：GeVec3dCR，一个三维向量的常量引用
		 *@return GeVec3d，以原点为起点该点为终点的向量与一个三维向量的叉积
		  
		*/
		GeVec3d operator^(GeVec3dCR vec) const;

		/**
		 *@brief 返回该点与一个标量的相除的结果
		 *@param denominator：double，一个标量，不能为0
		 *@return GePoint3d，一个新的三维点
		 *@note 原三维点没有发生变化
		*/
		GePoint3d operator/(double denominator) const;

		/**
		 *@brief 返回该点与一个三维点对应坐标是否相等
		 *@param point：GePoint3dCR，一个三维点的常量引用
		 *@return bool，相等为true，反之为false
		  
		*/
		bool operator==(GePoint3dCR point) const;
		/**
		 *@brief 返回该点与一个三维点对应坐标是否不相等
		 *@param point：GePoint3dCR，一个三维点的常量引用
		 *@return bool，不相等为true，反之为false
		  
		*/
		bool operator!=(GePoint3dCR point) const;

		/**
		 *@brief 重载下标运算符
				  如果idx = 0，则返回x的引用
				  如果idx = 1，则返回y的引用
				  如果idx = 2，则返回z的引用
		 *@param idx：int，坐标的 index
		 *@return double&，坐标的引用
		  
		*/
		double& operator[](int idx)
		{
			return *(&x + idx);
		}

		/**
		 *@brief 重载下标运算符的常量版本
				  如果idx = 0，则返回x的引用
				  如果idx = 1，则返回y的引用
				  如果idx = 2，则返回z的引用
		 *@param idx：int，坐标的 index
		 *@return const double&，坐标的引用
		 *@note 不能对返回的坐标的引用进行修改
		*/
		const double& operator[](int idx)const
		{
			return *(&x + idx);
		}
		/**
		 *@brief 将该点转换为一个三维向量
		 *@return GeVec3d，一个三维向量
		 *@note 该点不发生变化
		 */
		GeVec3d vec3d() const;


		/**
		 *@brief 创建一个三维点
		 *@param x: double, x坐标；
		 *@param y: double, y坐标；
		 *@param z: double, z坐标，默认值为0.0；
		 *@return GePoint3d，一个坐标类型为double的三维点
		  
		*/
		static GePoint3d create(double x, double y, double z = 0.0);


		/**
		 *@brief 创建一个三维点
		 *@param xy: 一个二维点的常量引用；
		 *@return GePoint3d，一个坐标类型为double的三维点
		 *@note 该三维点与二维点的对应坐标相等，z坐标为0.0
		*/
		static GePoint3d create(GePoint2dCR xy);


		/**
		 *@brief 创建一个三维点
		 *@return GePoint3d，一个坐标类型为double的三维点，x, y, z的值都为0.0
		  
		*/
		static GePoint3d createByZero();


		/*
		 *@brief 创建一个三维点
		 *@return GePoint3d，一个坐标类型为double的三维点，x, y 的值都为1.0
		  
		*/
		static GePoint3d createByUnify();









		/**
		 *@brief 交换两个点，该点的值和point发生互换
		 *@param point: GePoint3dR，一个三维点的引用；
		 *@return 
		  
		*/
		void swap(GePoint3dR point);


		/**
		 *@brief 返回以该点为起点，point1 和 point2 为终点的向量在 x,y 平面上的投影向量的叉乘的值
		 *@param point1：GePoint3dCR，一个三维点的常量引用；
		 *@param point2：GePoint3dCR，一个三维点的常量引用；
		 *@return double，该点为起点，point1 和 point2 为终点的向量在 x,y 平面上的投影向量的叉乘的值
		  
		*/
		double crossProductToPoints2D(GePoint3dCR point1, GePoint3dCR point2) const;





		/**
		 *@brief 返回以该点为起点，point1 和 point2 为终点的向量在 x,y 平面上的投影向量的点乘
		 *@param point1：GePoint3dCR，一个三维点的常量引用；
		 *@param point2：GePoint3dCR，一个三维点的常量引用；
		 *@return double，该点为起点，point1 和 point2 为终点的向量在 x,y 平面上的投影向量的点乘
		  
		*/
		double dotProductToPoints2D(GePoint3dCR point1, GePoint3dCR point2) const;






		/**
		 *@brief 将该点的坐标设置为（0.0， 0.0， 0.0）
		  
		*/
		void zero();


		/**
		 *@brief 将该点的坐标设置为（1.0， 1.0， 1.0）
		  
		*/
		void unify();







		/**
		 *@brief 设置该三维点的x,y,z坐标
		 *@param point2d：GePoint2dCR，一个二维点的常量引用
		 *@return 
		 *@note 该三维点与二维点对应坐标相等，z坐标为0；
		*/
		void set(GePoint2dCR point2d);


		/**
		 *@brief 设置该三维点的x,y,z坐标
		 *@param x: double, x坐标；
		 *@param y: double, y坐标；
		 *@param z: double, z坐标；
		 *@return 
		  
		*/
		void set(double x, double y, double z);


		/**
		 *@brief 设置该三维点的x,y,z坐标
		 *@param x: double, x坐标；
		 *@param y: double, y坐标；
		 *@return 
		 *@note z 坐标为 0.0
		*/
		void set(double x, double y);


		/**
		 *@brief 设置该三维点的x,y,z坐标
		 *@param point4d: GePoint4dCR，四维向量的常量引用；
		 *@return 
		  
		*/
		void set(GePoint4dCR point4d);
		/**
		 *@brief 创建一个三维点
		 *@param point4d: GePoint4dCR，一个的四维点的常量引用
		 *@return GePoint3d，一个三维点，三维点和四维点的对应坐标相等
		  
		*/
		static GePoint3d create(GePoint4dCR point4d);


		/**
		 *@brief 使用 index 来对坐标进行赋值：
					a) 如果 index % 3 == 0, 则 x = indexValue
					b) 如果 index % 3 == 1, 则 y = indexValue
					c) 如果 index % 3 == 2, 则 z = indexValue
					d) 如果 index 为负, 则根据 3-((-idx) % 3) 来进行赋值
		 *@param indexValue: double, 坐标值；
		 *@param index: int，坐标的 index
		 *@return 
		  
		*/
		void setCoordValueByIndex(double indexValue, int index);


		/**
		 *@brief 使用 index 来获取坐标值：
					a) 如果 index % 3 == 0, 则获得 x 的值
					b) 如果 index % 3 == 1, 则获得 y 的值
					c) 如果 index % 3 == 2, 则获得 z 的值
					d) 如果 index 为负, 则根据 3-((-idx) % 3) 来进行获值
		 *@param index: int，坐标的 index
		 *@return double，坐标值
		  
		*/
		double getCoordValueByIndex(int index) const;





		/**
		 *@brief 在以 point0 为起点 point1 为终点的向量上以 factionParameter 为比例进行插值，
				  该点设置为插值的结果
		 *@param point0: GePoint3dCR，一个三维点的常量引用；
		 *@param point1: GePoint3dCR，一个三维点的常量引用；
		 *@param fractionParameter: double 插值比例
		 *@return 
		  
		*/
		void interpolate(GePoint3dCR point0, double fractionParameter, GePoint3dCR point1);
		/**
		 *@brief 以 original 为起点，point1为终点构成了向量 vector1;
				  以 original 为起点，point2为终点构成了向量 vector2;
				  函数返回该点是否在 vector1 和 vector2 构成的较小扇形区域内的判定结果
		 *@param origin: GePoint3dCR，一个三维点的常量引用；
		 *@param point1: GePoint3dCR，一个三维点的常量引用；
		 *@param point2: GePoint3dCR，一个三维点的常量引用；
		 *@return bool，该点在 vector1 和 vector2 构成的较小扇形区域内返还 true，反之false
		  
		*/
		bool isPointInSmallerSector(GePoint3dCR origin, GePoint3dCR point1, GePoint3dCR point2) const;
		/**
		 *@brief 以 original 为起点，point0为终点构成了向量 vector0;
				  以 original 为起点，point1为终点构成了向量 vector1;
				  函数返回该点是否在以upVector为旋转正方向从 vector0 到 vector1 逆时针扫过的扇形区域内的判定结果
		 *@param origin: GePoint3dCR，一个三维点的常量引用；
		 *@param point0: GePoint3dCR，一个三维点的常量引用；
		 *@param point1: GePoint3dCR，一个三维点的常量引用；
		 *@param upVector: GeVec3dCR，一个三维向量的常量引用；
		 *@return bool，该点在以upVector为旋转轴正方向从 vector0 到 vector1 逆时针扫过得扇形区域内返还 true，反之false
		  
		*/
		bool isPointInCCWector(GePoint3dCR origin, GePoint3dCR point0, GePoint3dCR point1, GeVec3dCR upVector) const;
		/**
		 *@brief 计算 point 到该点的距离
		 *@param point: GePoint3dCR，一个三维点的常量引用；
		 *@return double，point 到该点的距离；
		  
		*/
		double distance(GePoint3dCR point) const;
		/**
		 *@brief 计算 point 到该点的距离的平方
		 *@param point: GePoint3dCR，一个三维点的常量引用；
		 *@return double，point 到该点的距离的平方；
		  
		*/
		double distanceSquared(GePoint3dCR point) const;


		/**
		 *@brief 计算 point 和该点在 x,y 平面上的投影点的距离
		 *@param point: GePoint3dCR，一个三维点的常量引用；
		 *@return double，point 和该点在 x,y 平面上的投影点的距离；
		  
		*/
		double distance2D(GePoint3dCR point) const;


		/**
		 *@brief 计算 point 和该点在 x,y 平面上的投影点的距离的平方
		 *@param point: GePoint3dCR，一个三维点的常量引用；
		 *@return double，point 和该点在 x,y 平面上的投影点的距离的平方；
		  
		*/
		double distanceSquared2D(GePoint3dCR point) const;


		/**
		 *@brief 将该点和point经过相同的变化后，计算变换后两点的距离
		 *@param point: GePoint3dCR，一个三维点的常量引用；
		 *@param matrix: GeMatrix4dCP，变换矩阵的常量指针；
		 *@param ditance: double 用于存放最终的结算结果；
		 *@return 返回bool，如果计算成功返还 true, 反之 false；
		 *@note 变换在齐次坐标下完成
		 */
		bool distance2D(GePoint3dCR point, GeMatrix4dCP matrix, double& distance) const;
		/**
		 *@brief 返回坐标值的最大绝对值
		 *@return double，坐标值的最大绝对值；
		 */
		double maxAbs() const;
		/**
		 *@brief 返回坐标值的最小绝对值
		 *@return double，坐标值的最小绝对值；
		 */
		double minAbs() const;
		/**
		 *@brief 返回绝对值最大的坐标对应的index
		 *@return int，坐标的index；
		 */
		int maxAbsIndex() const;
		/**
		 *@brief 返回绝对值最小的坐标对应的index
		 *@return int，坐标的index；
		*/
		int minAbsIndex() const;


		/**
		 *@brief 返回由坐标值组成的（min(x,y,z)，max(x,y,z)）范围
		 *@return GeRange1d, 坐标值组成的（min(x,y,z)，max(x,y,z)）范围
		*/
		GeRange1d componentRange() const;
		/**
		 *@brief 比较该点和 point 是否相等的结果
		 *@param point: GePoint3dCR,一个三维点的常量引用；
		 *@return bool,该点和 point 相等则返还true,反之返还 false;
		*/
		bool isEqual(GePoint3dCR point) const;

		/**
		 *@brief 比较该点和 point 在 tolerance 范围内是否相等的结果
		 *@param point:GePoint3dCR, 一个三维点的常量引用；
		 *@param tolerance: double, 误差容许范围；
		 *@return bool,该点和 point 在 tolerance 范围内相等则返还true,反之返还 false;
		*/
		bool isEqual(GePoint3dCR point2, double tolerance) const;

		/**
		 *@brief 将该点设置为 point 在 cube 中的归一化投影坐标
		 *@param point: GePoint3dCR，一个三维点的常量引用；
		 *@param cube: GeRange3dCR；
		 *@return 
		*/
		void npcCoordinatesOf(GePoint3dCR point, GeRange3dCR cube);
		/**
		 *@brief 判断该点的坐标中是否至少有一个为DISCONNECT
		 *@return bool，是则返回true，反之返回false；
		 */
		bool isDisconnect() const;


		/**
		 *@brief 设置该点的x,y，z坐标为Disconnect
		 */
		void setDisconnect();


		/**
		 *@brief 设置该三维点的x,y,z坐标
		 *@param vector：GeVec3dCR，一个三维向量的常量引用
		 *@return 
		  
		 */
		void set(GeVec3dCR vector);






		/**
		 *@brief 将一个数组 points中所有点与point对应坐标相加
		 *@param points：GePoint3dP，指向数组首元素的指针
		 *@param n：int 点的个数
		 *@param point：GePoint3dCR，一个三维点的常量引用
		 *@return 
		  
		 */
		static void addToArray(GePoint3dP points, int n, GePoint3dCR point);

















		/**
		 *@brief 将该点与point在 x,y平面上的投影做叉积
		 *@param point：GePoint3dCR，一个三维点的常量引用
		 *@return double，该点与point在 x,y平面上的投影做叉积的值
		  
		 */
		double crossProduct2D(GePoint3dCR point) const;






















		/**
		 *@brief 将该点与point在x,y平面上的投影做点积
		 *@param point：GePoint3dCR，一个三维点的常量引用
		 *@return double，该点与point在 x,y平面上的投影点积的值
		  
		 */
		double dotProduct2D(GePoint3dCR point) const;











		/**
		 *@brief 返回以原点旋转中心该点旋转到point的旋转角度
		 *@param point：GePoint3dCR，一个三维点的常量引用
		 *@return double，以原点旋转中心该点旋转到point的旋转角度
		  
		 */
		double getAngleTo(GePoint3dCR point) const;


		/**
		 *@brief 返回以原点为起点该点在x, y平面的投影点为终点的向量与 x 轴正方向之间的夹角
		 *@return double，夹角
		  
		 */
		double getAngleTo2D() const;

		/**
		 *@brief 返回以原点为起点该点与point为终点的向量之间的夹角或者补角，取较小的那个
		 *@param point：GePoint3dCR，一个三维点的常量引用
		 *@return double，原点为起点该点与point为终点的向量之间的夹角或者补角，取较小的那个
		  
		 */
		double smallerUnorientedAngleTo(GePoint3dCR point) const;
		/**
		 *@brief 以原点为起点，point0为终点构成的向量 vector1;
				  以原点为起点，point1为终点构成的向量 vector2;
				  函数返回该点是否在 vector1 和 vector2 构成的较小扇形区域内的判定结果
		 *@param point0: GePoint3dCR，一个三维点的常量引用；
		 *@param point1: GePoint3dCR，一个三维点的常量引用；
		 *@return bool，该点在 vector1 和 vector2 构成的较小扇形区域内返还 true，反之false
		  
		*/
		bool isVectorInSmallerSector(GePoint3dCR point0, GePoint3dCR point1) const;
		/**
		 *@brief 以原点为起点，point0为终点构成了向量 vector0;
				  以原点为起点，point1为终点构成了向量 vector1;
				  函数返回该点是否在以upVector为旋转轴的正方向从 vector0 到 vector1 逆时针扫过的扇形区域内的判定结果
		 *@param point0: GePoint3dCR，一个三维点的常量引用；
		 *@param point1: GePoint3dCR，一个三维点的常量引用；
		 *@param upVector: GePoint3dCR，一个三维向量的常量引用；
		 *@return bool，该点是否在以upVector为旋转正方向从 vector0 到 vector1 逆时针扫过得扇形区域内返还 true，反之false
		  
		 */
		bool isVectorInCCWSector(GePoint3dCR point0, GePoint3dCR point1, GePoint3dCR upVector) const;


		/**
		 *@brief 返回以原点为起点 该点 与 point 为终点的向量在x, y平面上的投影向量之间的夹角
		 *@param point：GePoint3dCR，一个三维点的常量引用
		 *@return double，向量之间的夹角
		  
		 */
		double angleTo2D(GePoint3dCR point) const;
		/**
		 *@brief 返回以原点为起点 该点 与 point 为终点的向量在x, y平面上的投影向量之间的夹角或者补角，取较小的那个
		 *@param point：GePoint3dCR，一个三维点的常量引用
		 *@return double，原点为起点 该点 与 point 为终点的向量之间的夹角或者补角，取较小的那个
		  
		 */
		double smallerUnorientedAngleTo2D(GePoint3dCR point) const;


		/**
		 *@brief vector逆时针绕 z 轴旋转 theta 角度，将该点设置为结果；
		 *@param vector：GePoint3dCR，一个三维点的常量引用
		 *@param theta：double，旋转角度
		 *@return 
		  
		 */
		void rotate2D(GePoint3dCR vector, double theta);


		/**
		 *@brief 以原点为起点，该点为终点的向量在x, y平面上的投影向量逆时针绕 z 轴旋转 theta 角度得到一个投影向量vector1；
				  设置该点的值，使得以原点为起点，该点为终点的向量在x, y平面上的投影向量与vector1重合；
		 *@param theta：double，旋转角度
		 *@return 
		  
		 */
		void rotate2D(double theta);

		/**
		 *@brief 以原点为旋转中心，orientationVector为旋转轴的正方向，从该点到point的旋转角度
		 *@param point：GePoint3dCR
		 *@param orientationVector：GePoint3dCR，向量端点
		 *@return double，旋转角度
		  
		 */
		double signedAngleTo(GePoint3dCR point, GePoint3dCR orientationVector) const;

		/**
		 *@brief 以原点为起点以该点和point2为终点的向量，在以planeNormal为法向量，原点为origin的平面上
				 的投影点，以planeNormal为旋转正方向的夹角
		 *@param point2：GePoint3dCR
		 *@param planeNormal：GePoint3dCR，平面的法向量
		 *@return double，旋转角度
		  
		 */
		double planarAngleTo(GePoint3dCR point2, GePoint3dCR planeNormal) const;



















		/**
		 *@brief 返回以原点到该点距离的平方
		 *@return double，返回以原点到该点距离的平方
		  
		 */
		double magnitudeSquared() const;


		/**
		 *@brief 返回以原点到该点在x,y平面投影的距离
		 *@return double，返回以原点到该点距离的平方
		  
		 */
		double magnitude2D() const;


		/**
		 *@brief 返回以原点到该点在x,y平面投影的距离的平方
		 *@return double，返回以原点到该点在x,y平面投影的距离的平方
		  
		 */
		double magnitudeSquared2D() const;


		/**
		 *@brief 将该点设置为与以原点为起点vector为终点的向量在x,y平面的投影正交的单位向量
		 *@return bool，成功返还true，失败返还false；
		  
		 */
		bool unitPerpendicular2D(GePoint3dCR vector);
		/**
		 *@brief 返回以原点到该点距离
		 *@return double，返回以原点到该点距离
		  
		 */
		double magnitude() const;












		/**
		 *@brief 将该点做原点堆成变换
		  
		 */
		void negate();

		/**
		 *@brief 对 vector 做归一化，返回vector到原点的距离，将该点设置为归一化后的结果
		 *@param vector：GePoint3dCR，一个三维点的常量引用
		 *@return double，返回以原点到该点距离
		  
		 */
		double normalize(GePoint3dCR vector);









		/**
		 *@brief 对该点做归一化，返回该点到原点的距离
		 *@return double，返回原点到该点距离
		  
		 */
		double normalize();
		/**
		 *@brief 判断以坐标原点为起点该点和point2为终点的向量是否平行
		 *@param point2：GePoint3dCR，一个三维点的常量引用
		 *@return bool，平行返还true，反之false
		  
		 */
		bool isParallelTo(GePoint3dCR point2) const;
		/**
		 *@brief 判断以坐标原点为起点该点和point2为终点的向量是否垂直
		 *@param point2：GePoint3dCR，一个三维点的常量引用
		 *@return bool，垂直返还true，反之false
		  
		 */
		bool isPerpendicularTo(GePoint3dCR point2) const;
		/**
		 *@brief 将 point 除以标量 denominator结果赋值给该点
		 *@param point：GePoint3dCR，一个三维点的常量引用
		 *@param denominator：double，标量
		 *@return bool, denominator非0，返回true；反之返回false
		 *@note  denominator为0，该点就直接等于 point
		 */
		bool safeDivide(GePoint3dCR point, double denominator);








































		/**
		 *@brief 以原点为起点，该点为终点的向量为z轴pZAxis；
				  如果pZAxis几乎与(0,0,1)重合，vector = (0,1,0), 否则 vector = (0,0,1);
				  pXAxis = vector ^ pZAxis, pYAxis = pZAxis ^ pXAxis;
				  pXAxis = normalize(pXAxis);
				  pYAxis = normalzie(pYAxis);
				  pZAxis = normalzie(pZAxis);
				  最后得到以该向量为z轴的一组基
		 *@param pXAxis：GePoint3dR，指向元素为三维点的数组首元素的指针
		 *@param pYAxis：GePoint3dR，指向元素为三维点的数组首元素的指针
		 *@param pZAxis：GePoint3dR，指向元素为double的数组首元素的指针
		  
		 */
		bool getNormalizedTriad(GePoint3dR pXAxis, GePoint3dR pYAxis, GePoint3dR pZAxis) const;
		/**
		 *@brief 将 pSource 中的点与 pScale 中的对应标量相乘后的结果存放在 pDest 中
		 *@param pDest：GePoint3dP，指向元素为三维点的数组首元素的指针
		 *@param pSource：GePoint3dCP，指向元素为三维点的数组首元素的指针
		 *@param pScales：double*，指向元素为double的数组首元素的指针
		 *@param n: int, pSource, pDest, pScale中元素的数量
		  
		 */
		static void multiplyArrayByScales(GePoint3dP pDest, GePoint3dCP pSource, double* pScales, int n);

		/**
		 *@brief 将 pSource 中的点与 pScale 中的对应标量相除后的结果存放在 pDest 中
		 *@param pDest：GePoint3dP，指向元素为三维点的数组首元素的指针
		 *@param pSource：GePoint3dCP，指向元素为三维点的数组首元素的指针
		 *@param pScales：double*，指向元素为double的数组首元素的指针
		 *@param n: int, pSource, pDest, pScale中元素的数量
		  
		 */
		static void divideArrayByScales(GePoint3dP pDest, GePoint3dCP pSource, double* pScales, int n);


		/**
		 *@brief 返还 (x,y,z) 经过变换之后的点
		 *@param x：double, 点的 x 坐标
		 *@param y：double, 点的 y 坐标
		 *@param z：double, 点的 z 坐标
		 *@param transform: GeTransformCR，变换矩阵
		  
		 */
		static GePoint3d createByTransform(GeTransformCR transform, double x, double y, double z);


		/**
		 *@brief 返还 point 经过变换之后的点
		 *@param point：GePoint3dCR，一个三维点的常量引用
		 *@param transform: GeTransformCR，变换矩阵
		  
		 */
		static GePoint3d createByTransform(GeTransformCR transform, GePoint3dCR point);


		/**
		 *@brief 在以 pointA 为起点 pointB 为终点的向量上以 fraction 为比例进行插值，
				  返回最后得到的插值点
		 *@param pointA: GePoint3dCR，一个三维点的常量引用；
		 *@param pointB: GePoint3dCR，一个三维点的常量引用；
		 *@param fraction: double 插值比例
		 *@return GePoint3d，返回最后得到的插值点
		  
		*/
		static GePoint3d createByInterpolate(GePoint3dCR pointA, double fraction, GePoint3dCR pointB);


		/**
		 *@brief 返回在 point00，point10，point01，point11 围成的区域内以比例 u, v 做双线性插值的结果
		 *@param point00: GePoint3dCR，一个三维点的常量引用；
		 *@param point10: GePoint3dCR，一个三维点的常量引用；
		 *@param point01: GePoint3dCR，一个三维点的常量引用；
		 *@param point11: GePoint3dCR，一个三维点的常量引用；
		 *@param u: double 插值比例
		 *@param v: double 插值比例
		 *@return GePoint3d，返回最后得到的插值点
		  
		*/
		static GePoint3d createByInterpolateBilinear(GePoint3dCR point00, GePoint3dCR point10, GePoint3dCR point01, GePoint3dCR point11, double u, double v);
































		/**
		 *@brief 将点(x,y,z）做matrix定义的旋转变换和point定义的平移变换。
		 *@param point: GePoint3dCR，一个三维点的常量引用；
		 *@param matrix: GeRotMatrixCR，旋转变换矩阵；
		 *@param x：double, 点的 x 坐标
		 *@param y：double, 点的 y 坐标
		 *@param z：double, 点的 z 坐标
		 *@return GePoint3d，得到变换后的点
		  
		*/
		static GePoint3d createByRotate(GePoint3dCR point, GeRotMatrixCR matrix, double x, double y, double z);


		/**
		 *@brief 将向量的 vector 的端点做matrix定义的旋转变换和point定义的平移变换。
		 *@param point: GePoint3dCR，一个三维点的常量引用；
		 *@param matrix:GeRotMatrixCR，旋转变换矩阵；
		 *@param vector: GeVec3dCR，一个三维向量的常量引用；
		 *@return GePoint3d，得到变换后的点
		  
		*/
		static GePoint3d createByRotate(GePoint3dCR point, GeRotMatrixCR matrix, GeVec3dCR vector);

		/**
		 *@brief 判断在误差容许范围内该点和point是否相等
		 *@param point: GePoint3d const&
		 *@return bool，相等则返还true，否则返还false；
		*/
		bool almostEqual(GePoint3d const& point) const;


		/**
		 *@brief 判断在误差容许范围内该点和point在x，y平面上的投影点是否相等
		  *@param point: GePoint3d const&
		 *@return bool，相等则返还true，否则返还false；
		*/
		bool almostEqual2D(GePoint3d const& point) const;


		/**
		 *@brief 判断在绝对值误差容许范围abstol内该点和point是否相等
		 *@param point: GePoint3d const&
		 *@param abstol: double
		 *@return bool，相等则返还true，否则返还false；
		*/
		bool almostEqual(GePoint3d const& point, double abstol) const;


		/**
		 *@brief 判断在绝对值误差容许范围abstol内该点和point在x， y平面上的投影是否相等
		 *@param point: GePoint3d const&
		 *@param abstol: double
		 *@return bool，相等则返还true，否则返还false；
		*/
		bool almostEqual2D(GePoint3d const& point, double abstol) const;




		/**
		 *@brief 判断在tolerance内left和right中对应的点是否相等
		 *@param left: pvector<GePoint3d> const&
		 *@param right: pvector<GePoint3d> const&
		 *@param tolerance:double，默认值为0.0
		 *@return bool，相等则返还true，否则返还false；
		*/
		static bool almostEqual(pvector<GePoint3d> const& left, pvector<GePoint3d> const& right, double tolerance = 0.0);



		/**
		 *@brief 判断在tolerance内left和right中对应的点在x, y平面上的投影是否相等
		 *@param left: pvector<GePoint3d> const&
		 *@param right: pvector<GePoint3d> const&
		 *@param tolerance:double，默认值为0.0
		 *@return bool，相等则返还true，否则返还false；
		*/
		static bool almostEqual2D(pvector<GePoint3d> const& left, pvector<GePoint3d> const& right, double tolerance = 0.0);

	};

};

#endif