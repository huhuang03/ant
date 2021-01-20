/*
 * This source file is part of RmlUi, the HTML/CSS Interface Middleware
 *
 * For the latest information, see http://github.com/mikke89/RmlUi
 *
 * Copyright (c) 2014 Markus Schöngart
 * Copyright (c) 2019 The RmlUi Team, and contributors
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 *
 */

#include "../Include/RmlUi/Transform.h"
#include "../Include/RmlUi/StyleSheetSpecification.h"
#include "../Include/RmlUi/TransformPrimitive.h"
#include "../Include/RmlUi/Property.h"
#include "TransformUtilities.h"

namespace Rml {

// Default constructor, initializes an identity transform
Transform::Transform()
{
}

Transform::Transform(PrimitiveList primitives) 
	: primitives(primitives)
{
}

Property Transform::MakeProperty(PrimitiveList primitives)
{
	Property p{ TransformPtr{new Transform{primitives}}, Property::TRANSFORM };
	p.definition = StyleSheetSpecification::GetProperty(PropertyId::Transform);
	return p;
}

void Transform::ClearPrimitives() 
{
	primitives.clear();
}

void Transform::AddPrimitive(const TransformPrimitive & p)
{
	primitives.push_back(p);
}

bool Transform::Empty() const {
	return primitives.empty();
}

glm::mat4x4 Transform::GetMatrix(Element& e) {
	glm::mat4x4 matrix(1);
	for (const TransformPrimitive& primitive : primitives) {
		matrix *= TransformUtilities::ResolveTransform(primitive, e);
	}
	return std::move(matrix);
}

} // namespace Rml
