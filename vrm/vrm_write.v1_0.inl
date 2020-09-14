static const char* cgltf_vrmc_vrm_blendshape_blendshapegroup_materialvalue_type_v1_0_to_str(const cgltf_vrmc_vrm_blendshape_blendshapegroup_materialvalue_type_v1_0 in) {
	switch (in) {
		case cgltf_vrmc_vrm_blendshape_blendshapegroup_materialvalue_type_v1_0_color: return "color";
		case cgltf_vrmc_vrm_blendshape_blendshapegroup_materialvalue_type_v1_0_emissionColor: return "emissionColor";
		case cgltf_vrmc_vrm_blendshape_blendshapegroup_materialvalue_type_v1_0_shadeColor: return "shadeColor";
		case cgltf_vrmc_vrm_blendshape_blendshapegroup_materialvalue_type_v1_0_rimColor: return "rimColor";
		case cgltf_vrmc_vrm_blendshape_blendshapegroup_materialvalue_type_v1_0_outlineColor: return "outlineColor";
		default: return "";
	}
}

static const char* cgltf_vrmc_vrm_blendshape_blendshapegroup_preset_v1_0_to_str(const cgltf_vrmc_vrm_blendshape_blendshapegroup_preset_v1_0 in) {
	switch (in) {
		case cgltf_vrmc_vrm_blendshape_blendshapegroup_preset_v1_0_custom: return "custom";
		case cgltf_vrmc_vrm_blendshape_blendshapegroup_preset_v1_0_aa: return "aa";
		case cgltf_vrmc_vrm_blendshape_blendshapegroup_preset_v1_0_ih: return "ih";
		case cgltf_vrmc_vrm_blendshape_blendshapegroup_preset_v1_0_ou: return "ou";
		case cgltf_vrmc_vrm_blendshape_blendshapegroup_preset_v1_0_ee: return "ee";
		case cgltf_vrmc_vrm_blendshape_blendshapegroup_preset_v1_0_oh: return "oh";
		case cgltf_vrmc_vrm_blendshape_blendshapegroup_preset_v1_0_blink: return "blink";
		case cgltf_vrmc_vrm_blendshape_blendshapegroup_preset_v1_0_joy: return "joy";
		case cgltf_vrmc_vrm_blendshape_blendshapegroup_preset_v1_0_angry: return "angry";
		case cgltf_vrmc_vrm_blendshape_blendshapegroup_preset_v1_0_sorrow: return "sorrow";
		case cgltf_vrmc_vrm_blendshape_blendshapegroup_preset_v1_0_fun: return "fun";
		case cgltf_vrmc_vrm_blendshape_blendshapegroup_preset_v1_0_lookUp: return "lookUp";
		case cgltf_vrmc_vrm_blendshape_blendshapegroup_preset_v1_0_lookDown: return "lookDown";
		case cgltf_vrmc_vrm_blendshape_blendshapegroup_preset_v1_0_lookLeft: return "lookLeft";
		case cgltf_vrmc_vrm_blendshape_blendshapegroup_preset_v1_0_lookRight: return "lookRight";
		case cgltf_vrmc_vrm_blendshape_blendshapegroup_preset_v1_0_blinkLeft: return "blinkLeft";
		case cgltf_vrmc_vrm_blendshape_blendshapegroup_preset_v1_0_blinkRight: return "blinkRight";
		case cgltf_vrmc_vrm_blendshape_blendshapegroup_preset_v1_0_neutral: return "neutral";
		default: return "";
	}
}

static const char* cgltf_vrmc_vrm_firstperson_meshannotation_firstPersonType_v1_0_to_str(const cgltf_vrmc_vrm_firstperson_meshannotation_firstPersonType_v1_0 in) {
	switch (in) {
		case cgltf_vrmc_vrm_firstperson_meshannotation_firstPersonType_v1_0_auto: return "auto";
		case cgltf_vrmc_vrm_firstperson_meshannotation_firstPersonType_v1_0_both: return "both";
		case cgltf_vrmc_vrm_firstperson_meshannotation_firstPersonType_v1_0_thirdPersonOnly: return "thirdPersonOnly";
		case cgltf_vrmc_vrm_firstperson_meshannotation_firstPersonType_v1_0_firstPersonOnly: return "firstPersonOnly";
		default: return "";
	}
}

static const char* cgltf_vrmc_vrm_lookat_lookAtType_v1_0_to_str(const cgltf_vrmc_vrm_lookat_lookAtType_v1_0 in) {
	switch (in) {
		case cgltf_vrmc_vrm_lookat_lookAtType_v1_0_bone: return "bone";
		case cgltf_vrmc_vrm_lookat_lookAtType_v1_0_blendShape: return "blendShape";
		default: return "";
	}
}

static const char* cgltf_vrmc_vrm_meta_avatarPermission_v1_0_to_str(const cgltf_vrmc_vrm_meta_avatarPermission_v1_0 in) {
	switch (in) {
		case cgltf_vrmc_vrm_meta_avatarPermission_v1_0_OnlyAuthor: return "OnlyAuthor";
		case cgltf_vrmc_vrm_meta_avatarPermission_v1_0_ExplicitlyLicensedPerson: return "ExplicitlyLicensedPerson";
		case cgltf_vrmc_vrm_meta_avatarPermission_v1_0_Everyone: return "Everyone";
		default: return "";
	}
}

static const char* cgltf_vrmc_vrm_meta_commercialUsage_v1_0_to_str(const cgltf_vrmc_vrm_meta_commercialUsage_v1_0 in) {
	switch (in) {
		case cgltf_vrmc_vrm_meta_commercialUsage_v1_0_PersonalNonCommercialNonProfit: return "PersonalNonCommercialNonProfit";
		case cgltf_vrmc_vrm_meta_commercialUsage_v1_0_PersonalNonCommercialProfit: return "PersonalNonCommercialProfit";
		case cgltf_vrmc_vrm_meta_commercialUsage_v1_0_PersonalCommercial: return "PersonalCommercial";
		case cgltf_vrmc_vrm_meta_commercialUsage_v1_0_Corporation: return "Corporation";
		default: return "";
	}
}

static const char* cgltf_vrmc_vrm_meta_creditNotation_v1_0_to_str(const cgltf_vrmc_vrm_meta_creditNotation_v1_0 in) {
	switch (in) {
		case cgltf_vrmc_vrm_meta_creditNotation_v1_0_Required: return "Required";
		case cgltf_vrmc_vrm_meta_creditNotation_v1_0_Unnecessary: return "Unnecessary";
		case cgltf_vrmc_vrm_meta_creditNotation_v1_0_Abandoned: return "Abandoned";
		default: return "";
	}
}

static const char* cgltf_vrmc_vrm_meta_modify_v1_0_to_str(const cgltf_vrmc_vrm_meta_modify_v1_0 in) {
	switch (in) {
		case cgltf_vrmc_vrm_meta_modify_v1_0_Prohibited: return "Prohibited";
		case cgltf_vrmc_vrm_meta_modify_v1_0_Inherited: return "Inherited";
		case cgltf_vrmc_vrm_meta_modify_v1_0_NotInherited: return "NotInherited";
		default: return "";
	}
}
static void cgltf_write_vrmc_vrm_springbone_collidergroup_collider_v1_0(cgltf_write_context* context, const cgltf_vrmc_vrm_springbone_collidergroup_collider_v1_0* data) {
	cgltf_write_line(context, "{");
	cgltf_write_floatarrayprop(context, "offset", data->offset, data->offset_count);
	cgltf_write_floatprop_strict(context, "radius", data->radius);
	cgltf_write_line(context, "}");
}
static void cgltf_write_vrmc_vrm_springbone_bonegroup_v1_0(cgltf_write_context* context, const cgltf_vrmc_vrm_springbone_bonegroup_v1_0* data) {
	cgltf_write_line(context, "{");
	cgltf_write_strprop(context, "name", data->name);
	cgltf_write_floatprop_strict(context, "stiffness", data->stiffness);
	cgltf_write_floatprop_strict(context, "gravityPower", data->gravityPower);
	cgltf_write_floatarrayprop(context, "gravityDir", data->gravityDir, data->gravityDir_count);
	cgltf_write_floatprop_strict(context, "dragForce", data->dragForce);
	cgltf_write_intprop_strict(context, "center", data->center);
	cgltf_write_floatprop_strict(context, "hitRadius", data->hitRadius);
	cgltf_write_intarrayprop(context, "bones", data->bones, data->bones_count);
	cgltf_write_intarrayprop(context, "colliderGroups", data->colliderGroups, data->colliderGroups_count);
	cgltf_write_line(context, "}");
}
static void cgltf_write_vrmc_vrm_springbone_collidergroup_v1_0(cgltf_write_context* context, const cgltf_vrmc_vrm_springbone_collidergroup_v1_0* data) {
	cgltf_write_line(context, "{");
	cgltf_write_intprop_strict(context, "node", data->node);
	cgltf_write_line(context, "\"colliders\": [");
	for (cgltf_size i = 0; i < data->colliders_count; ++i) {
		cgltf_write_vrmc_vrm_springbone_collidergroup_collider_v1_0(context, data->colliders + i);
	}
	cgltf_write_line(context, "]");
	cgltf_write_line(context, "}");
}
static void cgltf_write_vrmc_vrm_springbone_v1_0(cgltf_write_context* context, const cgltf_vrmc_vrm_springbone_v1_0* data) {
	cgltf_write_line(context, "{");
	cgltf_write_line(context, "\"boneGroups\": [");
	for (cgltf_size i = 0; i < data->boneGroups_count; ++i) {
		cgltf_write_vrmc_vrm_springbone_bonegroup_v1_0(context, data->boneGroups + i);
	}
	cgltf_write_line(context, "]");
	cgltf_write_line(context, "\"colliderGroups\": [");
	for (cgltf_size i = 0; i < data->colliderGroups_count; ++i) {
		cgltf_write_vrmc_vrm_springbone_collidergroup_v1_0(context, data->colliderGroups + i);
	}
	cgltf_write_line(context, "]");
	cgltf_write_line(context, "}");
}
static void cgltf_write_vrmc_vrm_blendshape_blendshapegroup_blendshapebind_v1_0(cgltf_write_context* context, const cgltf_vrmc_vrm_blendshape_blendshapegroup_blendshapebind_v1_0* data) {
	cgltf_write_line(context, "{");
	cgltf_write_strprop(context, "node", data->node);
	cgltf_write_strprop(context, "index", data->index);
	cgltf_write_floatprop_strict(context, "weight", data->weight);
	cgltf_write_line(context, "}");
}
static void cgltf_write_vrmc_vrm_blendshape_blendshapegroup_materialuvbind_v1_0(cgltf_write_context* context, const cgltf_vrmc_vrm_blendshape_blendshapegroup_materialuvbind_v1_0* data) {
	cgltf_write_line(context, "{");
	cgltf_write_intprop_strict(context, "material", data->material);
	cgltf_write_floatarrayprop(context, "scaling", data->scaling, data->scaling_count);
	cgltf_write_floatarrayprop(context, "offset", data->offset, data->offset_count);
	cgltf_write_line(context, "}");
}
static void cgltf_write_vrmc_vrm_blendshape_blendshapegroup_materialvalue_v1_0(cgltf_write_context* context, const cgltf_vrmc_vrm_blendshape_blendshapegroup_materialvalue_v1_0* data) {
	cgltf_write_line(context, "{");
	cgltf_write_intprop_strict(context, "material", data->material);
	cgltf_write_strprop(context, "type", cgltf_vrmc_vrm_blendshape_blendshapegroup_materialvalue_type_v1_0_to_str(data->type));
	cgltf_write_floatarrayprop(context, "targetValue", data->targetValue, data->targetValue_count);
	cgltf_write_line(context, "}");
}
static void cgltf_write_vrmc_vrm_blendshape_blendshapegroup_v1_0(cgltf_write_context* context, const cgltf_vrmc_vrm_blendshape_blendshapegroup_v1_0* data) {
	cgltf_write_line(context, "{");
	cgltf_write_strprop(context, "name", data->name);
	cgltf_write_strprop(context, "preset", cgltf_vrmc_vrm_blendshape_blendshapegroup_preset_v1_0_to_str(data->preset));
	cgltf_write_line(context, "\"binds\": [");
	for (cgltf_size i = 0; i < data->binds_count; ++i) {
		cgltf_write_vrmc_vrm_blendshape_blendshapegroup_blendshapebind_v1_0(context, data->binds + i);
	}
	cgltf_write_line(context, "]");
	cgltf_write_line(context, "\"materialValues\": [");
	for (cgltf_size i = 0; i < data->materialValues_count; ++i) {
		cgltf_write_vrmc_vrm_blendshape_blendshapegroup_materialvalue_v1_0(context, data->materialValues + i);
	}
	cgltf_write_line(context, "]");
	cgltf_write_line(context, "\"materialUVBinds\": [");
	for (cgltf_size i = 0; i < data->materialUVBinds_count; ++i) {
		cgltf_write_vrmc_vrm_blendshape_blendshapegroup_materialuvbind_v1_0(context, data->materialUVBinds + i);
	}
	cgltf_write_line(context, "]");
	cgltf_write_boolprop_strict(context, "isBinary", data->isBinary);
	cgltf_write_boolprop_strict(context, "ignoreBlink", data->ignoreBlink);
	cgltf_write_boolprop_strict(context, "ignoreLookAt", data->ignoreLookAt);
	cgltf_write_boolprop_strict(context, "ignoreMouth", data->ignoreMouth);
	cgltf_write_line(context, "}");
}
static void cgltf_write_vrmc_vrm_blendshape_v1_0(cgltf_write_context* context, const cgltf_vrmc_vrm_blendshape_v1_0* data) {
	cgltf_write_line(context, "{");
	cgltf_write_line(context, "\"blendShapeGroups\": [");
	for (cgltf_size i = 0; i < data->blendShapeGroups_count; ++i) {
		cgltf_write_vrmc_vrm_blendshape_blendshapegroup_v1_0(context, data->blendShapeGroups + i);
	}
	cgltf_write_line(context, "]");
	cgltf_write_line(context, "}");
}
static void cgltf_write_vrmc_vrm_constraint_v1_0(cgltf_write_context* context, const cgltf_vrmc_vrm_constraint_v1_0* data) {
	cgltf_write_line(context, "{");
	cgltf_write_line(context, "}");
}
static void cgltf_write_vrmc_vrm_firstperson_meshannotation_v1_0(cgltf_write_context* context, const cgltf_vrmc_vrm_firstperson_meshannotation_v1_0* data) {
	cgltf_write_line(context, "{");
	cgltf_write_strprop(context, "node", data->node);
	cgltf_write_strprop(context, "firstPersonType", cgltf_vrmc_vrm_firstperson_meshannotation_firstPersonType_v1_0_to_str(data->firstPersonType));
	cgltf_write_line(context, "}");
}
static void cgltf_write_vrmc_vrm_firstperson_v1_0(cgltf_write_context* context, const cgltf_vrmc_vrm_firstperson_v1_0* data) {
	cgltf_write_line(context, "{");
	cgltf_write_line(context, "\"meshAnnotations\": [");
	for (cgltf_size i = 0; i < data->meshAnnotations_count; ++i) {
		cgltf_write_vrmc_vrm_firstperson_meshannotation_v1_0(context, data->meshAnnotations + i);
	}
	cgltf_write_line(context, "]");
	cgltf_write_line(context, "}");
}
static void cgltf_write_vrmc_vrm_humanoid_humanbones_humanbone_v1_0(cgltf_write_context* context, const cgltf_vrmc_vrm_humanoid_humanbones_humanbone_v1_0* data) {
	cgltf_write_line(context, "{");
	cgltf_write_intprop_strict(context, "node", data->node);
	cgltf_write_line(context, "}");
}
static void cgltf_write_vrmc_vrm_humanoid_humanbones_v1_0(cgltf_write_context* context, const cgltf_vrmc_vrm_humanoid_humanbones_v1_0* data) {
	cgltf_write_line(context, "{");
	cgltf_write_line(context, "\"hips\": ");
	cgltf_write_vrmc_vrm_humanoid_humanbones_humanbone_v1_0(context, &data->hips);
	cgltf_write_line(context, "\"spine\": ");
	cgltf_write_vrmc_vrm_humanoid_humanbones_humanbone_v1_0(context, &data->spine);
	cgltf_write_line(context, "\"chest\": ");
	cgltf_write_vrmc_vrm_humanoid_humanbones_humanbone_v1_0(context, &data->chest);
	cgltf_write_line(context, "\"upperChest\": ");
	cgltf_write_vrmc_vrm_humanoid_humanbones_humanbone_v1_0(context, &data->upperChest);
	cgltf_write_line(context, "\"neck\": ");
	cgltf_write_vrmc_vrm_humanoid_humanbones_humanbone_v1_0(context, &data->neck);
	cgltf_write_line(context, "\"head\": ");
	cgltf_write_vrmc_vrm_humanoid_humanbones_humanbone_v1_0(context, &data->head);
	cgltf_write_line(context, "\"leftEye\": ");
	cgltf_write_vrmc_vrm_humanoid_humanbones_humanbone_v1_0(context, &data->leftEye);
	cgltf_write_line(context, "\"rightEye\": ");
	cgltf_write_vrmc_vrm_humanoid_humanbones_humanbone_v1_0(context, &data->rightEye);
	cgltf_write_line(context, "\"jaw\": ");
	cgltf_write_vrmc_vrm_humanoid_humanbones_humanbone_v1_0(context, &data->jaw);
	cgltf_write_line(context, "\"leftUpperLeg\": ");
	cgltf_write_vrmc_vrm_humanoid_humanbones_humanbone_v1_0(context, &data->leftUpperLeg);
	cgltf_write_line(context, "\"leftLowerLeg\": ");
	cgltf_write_vrmc_vrm_humanoid_humanbones_humanbone_v1_0(context, &data->leftLowerLeg);
	cgltf_write_line(context, "\"leftFoot\": ");
	cgltf_write_vrmc_vrm_humanoid_humanbones_humanbone_v1_0(context, &data->leftFoot);
	cgltf_write_line(context, "\"leftToes\": ");
	cgltf_write_vrmc_vrm_humanoid_humanbones_humanbone_v1_0(context, &data->leftToes);
	cgltf_write_line(context, "\"rightUpperLeg\": ");
	cgltf_write_vrmc_vrm_humanoid_humanbones_humanbone_v1_0(context, &data->rightUpperLeg);
	cgltf_write_line(context, "\"rightLowerLeg\": ");
	cgltf_write_vrmc_vrm_humanoid_humanbones_humanbone_v1_0(context, &data->rightLowerLeg);
	cgltf_write_line(context, "\"rightFoot\": ");
	cgltf_write_vrmc_vrm_humanoid_humanbones_humanbone_v1_0(context, &data->rightFoot);
	cgltf_write_line(context, "\"rightToes\": ");
	cgltf_write_vrmc_vrm_humanoid_humanbones_humanbone_v1_0(context, &data->rightToes);
	cgltf_write_line(context, "\"leftShoulder\": ");
	cgltf_write_vrmc_vrm_humanoid_humanbones_humanbone_v1_0(context, &data->leftShoulder);
	cgltf_write_line(context, "\"leftUpperArm\": ");
	cgltf_write_vrmc_vrm_humanoid_humanbones_humanbone_v1_0(context, &data->leftUpperArm);
	cgltf_write_line(context, "\"leftLowerArm\": ");
	cgltf_write_vrmc_vrm_humanoid_humanbones_humanbone_v1_0(context, &data->leftLowerArm);
	cgltf_write_line(context, "\"leftHand\": ");
	cgltf_write_vrmc_vrm_humanoid_humanbones_humanbone_v1_0(context, &data->leftHand);
	cgltf_write_line(context, "\"rightShoulder\": ");
	cgltf_write_vrmc_vrm_humanoid_humanbones_humanbone_v1_0(context, &data->rightShoulder);
	cgltf_write_line(context, "\"rightUpperArm\": ");
	cgltf_write_vrmc_vrm_humanoid_humanbones_humanbone_v1_0(context, &data->rightUpperArm);
	cgltf_write_line(context, "\"rightLowerArm\": ");
	cgltf_write_vrmc_vrm_humanoid_humanbones_humanbone_v1_0(context, &data->rightLowerArm);
	cgltf_write_line(context, "\"rightHand\": ");
	cgltf_write_vrmc_vrm_humanoid_humanbones_humanbone_v1_0(context, &data->rightHand);
	cgltf_write_line(context, "\"leftThumbProximal\": ");
	cgltf_write_vrmc_vrm_humanoid_humanbones_humanbone_v1_0(context, &data->leftThumbProximal);
	cgltf_write_line(context, "\"leftThumbIntermediate\": ");
	cgltf_write_vrmc_vrm_humanoid_humanbones_humanbone_v1_0(context, &data->leftThumbIntermediate);
	cgltf_write_line(context, "\"leftThumbDistal\": ");
	cgltf_write_vrmc_vrm_humanoid_humanbones_humanbone_v1_0(context, &data->leftThumbDistal);
	cgltf_write_line(context, "\"leftIndexProximal\": ");
	cgltf_write_vrmc_vrm_humanoid_humanbones_humanbone_v1_0(context, &data->leftIndexProximal);
	cgltf_write_line(context, "\"leftIndexIntermediate\": ");
	cgltf_write_vrmc_vrm_humanoid_humanbones_humanbone_v1_0(context, &data->leftIndexIntermediate);
	cgltf_write_line(context, "\"leftIndexDistal\": ");
	cgltf_write_vrmc_vrm_humanoid_humanbones_humanbone_v1_0(context, &data->leftIndexDistal);
	cgltf_write_line(context, "\"leftMiddleProximal\": ");
	cgltf_write_vrmc_vrm_humanoid_humanbones_humanbone_v1_0(context, &data->leftMiddleProximal);
	cgltf_write_line(context, "\"leftMiddleIntermediate\": ");
	cgltf_write_vrmc_vrm_humanoid_humanbones_humanbone_v1_0(context, &data->leftMiddleIntermediate);
	cgltf_write_line(context, "\"leftMiddleDistal\": ");
	cgltf_write_vrmc_vrm_humanoid_humanbones_humanbone_v1_0(context, &data->leftMiddleDistal);
	cgltf_write_line(context, "\"leftRingProximal\": ");
	cgltf_write_vrmc_vrm_humanoid_humanbones_humanbone_v1_0(context, &data->leftRingProximal);
	cgltf_write_line(context, "\"leftRingIntermediate\": ");
	cgltf_write_vrmc_vrm_humanoid_humanbones_humanbone_v1_0(context, &data->leftRingIntermediate);
	cgltf_write_line(context, "\"leftRingDistal\": ");
	cgltf_write_vrmc_vrm_humanoid_humanbones_humanbone_v1_0(context, &data->leftRingDistal);
	cgltf_write_line(context, "\"leftLittleProximal\": ");
	cgltf_write_vrmc_vrm_humanoid_humanbones_humanbone_v1_0(context, &data->leftLittleProximal);
	cgltf_write_line(context, "\"leftLittleIntermediate\": ");
	cgltf_write_vrmc_vrm_humanoid_humanbones_humanbone_v1_0(context, &data->leftLittleIntermediate);
	cgltf_write_line(context, "\"leftLittleDistal\": ");
	cgltf_write_vrmc_vrm_humanoid_humanbones_humanbone_v1_0(context, &data->leftLittleDistal);
	cgltf_write_line(context, "\"rightThumbProximal\": ");
	cgltf_write_vrmc_vrm_humanoid_humanbones_humanbone_v1_0(context, &data->rightThumbProximal);
	cgltf_write_line(context, "\"rightThumbIntermediate\": ");
	cgltf_write_vrmc_vrm_humanoid_humanbones_humanbone_v1_0(context, &data->rightThumbIntermediate);
	cgltf_write_line(context, "\"rightThumbDistal\": ");
	cgltf_write_vrmc_vrm_humanoid_humanbones_humanbone_v1_0(context, &data->rightThumbDistal);
	cgltf_write_line(context, "\"rightIndexProximal\": ");
	cgltf_write_vrmc_vrm_humanoid_humanbones_humanbone_v1_0(context, &data->rightIndexProximal);
	cgltf_write_line(context, "\"rightIndexIntermediate\": ");
	cgltf_write_vrmc_vrm_humanoid_humanbones_humanbone_v1_0(context, &data->rightIndexIntermediate);
	cgltf_write_line(context, "\"rightIndexDistal\": ");
	cgltf_write_vrmc_vrm_humanoid_humanbones_humanbone_v1_0(context, &data->rightIndexDistal);
	cgltf_write_line(context, "\"rightMiddleProximal\": ");
	cgltf_write_vrmc_vrm_humanoid_humanbones_humanbone_v1_0(context, &data->rightMiddleProximal);
	cgltf_write_line(context, "\"rightMiddleIntermediate\": ");
	cgltf_write_vrmc_vrm_humanoid_humanbones_humanbone_v1_0(context, &data->rightMiddleIntermediate);
	cgltf_write_line(context, "\"rightMiddleDistal\": ");
	cgltf_write_vrmc_vrm_humanoid_humanbones_humanbone_v1_0(context, &data->rightMiddleDistal);
	cgltf_write_line(context, "\"rightRingProximal\": ");
	cgltf_write_vrmc_vrm_humanoid_humanbones_humanbone_v1_0(context, &data->rightRingProximal);
	cgltf_write_line(context, "\"rightRingIntermediate\": ");
	cgltf_write_vrmc_vrm_humanoid_humanbones_humanbone_v1_0(context, &data->rightRingIntermediate);
	cgltf_write_line(context, "\"rightRingDistal\": ");
	cgltf_write_vrmc_vrm_humanoid_humanbones_humanbone_v1_0(context, &data->rightRingDistal);
	cgltf_write_line(context, "\"rightLittleProximal\": ");
	cgltf_write_vrmc_vrm_humanoid_humanbones_humanbone_v1_0(context, &data->rightLittleProximal);
	cgltf_write_line(context, "\"rightLittleIntermediate\": ");
	cgltf_write_vrmc_vrm_humanoid_humanbones_humanbone_v1_0(context, &data->rightLittleIntermediate);
	cgltf_write_line(context, "\"rightLittleDistal\": ");
	cgltf_write_vrmc_vrm_humanoid_humanbones_humanbone_v1_0(context, &data->rightLittleDistal);
	cgltf_write_line(context, "}");
}
static void cgltf_write_vrmc_vrm_humanoid_v1_0(cgltf_write_context* context, const cgltf_vrmc_vrm_humanoid_v1_0* data) {
	cgltf_write_line(context, "{");
	cgltf_write_line(context, "\"humanBones\": ");
	cgltf_write_vrmc_vrm_humanoid_humanbones_v1_0(context, &data->humanBones);
	cgltf_write_line(context, "}");
}
static void cgltf_write_vrmc_vrm_lookatrangemap_v1_0(cgltf_write_context* context, const cgltf_vrmc_vrm_lookatrangemap_v1_0* data) {
	cgltf_write_line(context, "{");
	cgltf_write_floatprop_strict(context, "inputMaxValue", data->inputMaxValue);
	cgltf_write_floatprop_strict(context, "outputScale", data->outputScale);
	cgltf_write_line(context, "}");
}
static void cgltf_write_vrmc_vrm_lookat_v1_0(cgltf_write_context* context, const cgltf_vrmc_vrm_lookat_v1_0* data) {
	cgltf_write_line(context, "{");
	cgltf_write_floatarrayprop(context, "offsetFromHeadBone", data->offsetFromHeadBone, data->offsetFromHeadBone_count);
	cgltf_write_strprop(context, "lookAtType", cgltf_vrmc_vrm_lookat_lookAtType_v1_0_to_str(data->lookAtType));
	cgltf_write_line(context, "\"lookAtHorizontalInner\": ");
	cgltf_write_vrmc_vrm_lookatrangemap_v1_0(context, &data->lookAtHorizontalInner);
	cgltf_write_line(context, "\"lookAtHorizontalOuter\": ");
	cgltf_write_vrmc_vrm_lookatrangemap_v1_0(context, &data->lookAtHorizontalOuter);
	cgltf_write_line(context, "\"lookAtVerticalDown\": ");
	cgltf_write_vrmc_vrm_lookatrangemap_v1_0(context, &data->lookAtVerticalDown);
	cgltf_write_line(context, "\"lookAtVerticalUp\": ");
	cgltf_write_vrmc_vrm_lookatrangemap_v1_0(context, &data->lookAtVerticalUp);
	cgltf_write_line(context, "}");
}
static void cgltf_write_vrmc_vrm_meta_v1_0(cgltf_write_context* context, const cgltf_vrmc_vrm_meta_v1_0* data) {
	cgltf_write_line(context, "{");
	cgltf_write_strprop(context, "name", data->name);
	cgltf_write_strprop(context, "version", data->version);
	cgltf_write_line(context, "\"authors\": [");
	for (cgltf_size i = 0; i < data->authors_count; ++i) {
		cgltf_write_strprop(context, "authors", data->authors + i);
	}
	cgltf_write_line(context, "]");
	cgltf_write_strprop(context, "copyrights", data->copyrights);
	cgltf_write_strprop(context, "contactInformation", data->contactInformation);
	cgltf_write_strprop(context, "reference", data->reference);
	cgltf_write_intprop_strict(context, "thumbnailImage", data->thumbnailImage);
	cgltf_write_strprop(context, "avatarPermission", cgltf_vrmc_vrm_meta_avatarPermission_v1_0_to_str(data->avatarPermission));
	cgltf_write_boolprop_strict(context, "violentUsage", data->violentUsage);
	cgltf_write_boolprop_strict(context, "sexualUsage", data->sexualUsage);
	cgltf_write_boolprop_strict(context, "gameUsage", data->gameUsage);
	cgltf_write_strprop(context, "commercialUsage", cgltf_vrmc_vrm_meta_commercialUsage_v1_0_to_str(data->commercialUsage));
	cgltf_write_boolprop_strict(context, "politicalOrReligiousUsage", data->politicalOrReligiousUsage);
	cgltf_write_strprop(context, "otherPermissionUrl", data->otherPermissionUrl);
	cgltf_write_strprop(context, "creditNotation", cgltf_vrmc_vrm_meta_creditNotation_v1_0_to_str(data->creditNotation));
	cgltf_write_boolprop_strict(context, "allowRedistribution", data->allowRedistribution);
	cgltf_write_strprop(context, "modify", cgltf_vrmc_vrm_meta_modify_v1_0_to_str(data->modify));
	cgltf_write_strprop(context, "otherLicenseUrl", data->otherLicenseUrl);
	cgltf_write_line(context, "}");
}
static void cgltf_write_vrmc_vrm_v1_0(cgltf_write_context* context, const cgltf_vrmc_vrm_v1_0* data) {
	cgltf_write_line(context, "{");
	cgltf_write_strprop(context, "specVersion", data->specVersion);
	cgltf_write_line(context, "\"meta\": ");
	cgltf_write_vrmc_vrm_meta_v1_0(context, &data->meta);
	cgltf_write_line(context, "\"humanoid\": ");
	cgltf_write_vrmc_vrm_humanoid_v1_0(context, &data->humanoid);
	cgltf_write_line(context, "\"firstPerson\": ");
	cgltf_write_vrmc_vrm_firstperson_v1_0(context, &data->firstPerson);
	cgltf_write_line(context, "\"lookAt\": ");
	cgltf_write_vrmc_vrm_lookat_v1_0(context, &data->lookAt);
	cgltf_write_line(context, "\"blendShape\": ");
	cgltf_write_vrmc_vrm_blendshape_v1_0(context, &data->blendShape);
	cgltf_write_line(context, "}");
}
