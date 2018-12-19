#pragma once

namespace Binding {

	struct IndexData {
		const int* indices;
		int count;
	};

	struct VertexData {
		const float* vertices;
		int componentCount;
		int count;
	};

	struct AttributeData {
		const int* attributeSizes;
		int count;
	};

	struct Bindable {
		VertexData vertexData;
		IndexData indexData;
		AttributeData attributeData;
	};

}

