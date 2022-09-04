var CK_COOL_CUSTOM_MACRO = 5
var CK_COOL_CUSTOM_MACRO2 = 6

class SkeletonReflect {
	static getCustomKeywords() {
		var s = CK_COOL_CUSTOM_MACRO.toString
		System.print("Hello World " + s)

		return [
			{
				"keyword": "COOL_CUSTOM_MACRO",
				"id": CK_COOL_CUSTOM_MACRO
			},
			{
				"keyword": "COOL_CUSTOM_MACRO2",
				"id": CK_COOL_CUSTOM_MACRO2
			},
		]
		
	}
}