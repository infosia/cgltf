static void cgltf_vrm_secondaryanimation_collidergroup_colliders_free(const struct cgltf_memory_options* memory, cgltf_vrm_secondaryanimation_collidergroup_colliders* data) {
	memory->free(memory->user_data, data->offset);
}
static void cgltf_vrm_secondaryanimation_spring_free(const struct cgltf_memory_options* memory, cgltf_vrm_secondaryanimation_spring* data) {
	memory->free(memory->user_data, data->comment);
	memory->free(memory->user_data, data->gravityDir);
	memory->free(memory->user_data, data->bones);
	memory->free(memory->user_data, data->colliderGroups);
}
static void cgltf_vrm_secondaryanimation_collidergroup_free(const struct cgltf_memory_options* memory, cgltf_vrm_secondaryanimation_collidergroup* data) {
	for (cgltf_size i = 0; i < data->colliders_count; i++) {
		cgltf_vrm_secondaryanimation_collidergroup_colliders_free(memory, &data->colliders[i]);
	}
	memory->free(memory->user_data, data->colliders);
}
static void cgltf_vrm_secondaryanimation_free(const struct cgltf_memory_options* memory, cgltf_vrm_secondaryanimation* data) {
	for (cgltf_size i = 0; i < data->boneGroups_count; i++) {
		cgltf_vrm_secondaryanimation_spring_free(memory, &data->boneGroups[i]);
	}
	memory->free(memory->user_data, data->boneGroups);
	for (cgltf_size i = 0; i < data->colliderGroups_count; i++) {
		cgltf_vrm_secondaryanimation_collidergroup_free(memory, &data->colliderGroups[i]);
	}
	memory->free(memory->user_data, data->colliderGroups);
}
static void cgltf_vrm_blendshape_bind_free(const struct cgltf_memory_options* memory, cgltf_vrm_blendshape_bind* data) {
	(void)memory;
	(void)data;
}
static void cgltf_vrm_blendshape_materialbind_free(const struct cgltf_memory_options* memory, cgltf_vrm_blendshape_materialbind* data) {
	memory->free(memory->user_data, data->materialName);
	memory->free(memory->user_data, data->propertyName);
	memory->free(memory->user_data, data->targetValue);
}
static void cgltf_vrm_blendshape_group_free(const struct cgltf_memory_options* memory, cgltf_vrm_blendshape_group* data) {
	memory->free(memory->user_data, data->name);
	for (cgltf_size i = 0; i < data->binds_count; i++) {
		cgltf_vrm_blendshape_bind_free(memory, &data->binds[i]);
	}
	memory->free(memory->user_data, data->binds);
	for (cgltf_size i = 0; i < data->materialValues_count; i++) {
		cgltf_vrm_blendshape_materialbind_free(memory, &data->materialValues[i]);
	}
	memory->free(memory->user_data, data->materialValues);
}
static void cgltf_vrm_blendshape_free(const struct cgltf_memory_options* memory, cgltf_vrm_blendshape* data) {
	for (cgltf_size i = 0; i < data->blendShapeGroups_count; i++) {
		cgltf_vrm_blendshape_group_free(memory, &data->blendShapeGroups[i]);
	}
	memory->free(memory->user_data, data->blendShapeGroups);
}
static void cgltf_vrm_firstperson_degreemap_free(const struct cgltf_memory_options* memory, cgltf_vrm_firstperson_degreemap* data) {
	memory->free(memory->user_data, data->curve);
}
static void cgltf_vrm_firstperson_meshannotation_free(const struct cgltf_memory_options* memory, cgltf_vrm_firstperson_meshannotation* data) {
	memory->free(memory->user_data, data->firstPersonFlag);
}
static void cgltf_vrm_firstperson_free(const struct cgltf_memory_options* memory, cgltf_vrm_firstperson* data) {
	memory->free(memory->user_data, data->firstPersonBoneOffset);
	for (cgltf_size i = 0; i < data->meshAnnotations_count; i++) {
		cgltf_vrm_firstperson_meshannotation_free(memory, &data->meshAnnotations[i]);
	}
	memory->free(memory->user_data, data->meshAnnotations);
	cgltf_vrm_firstperson_degreemap_free(memory, &data->lookAtHorizontalInner);
	cgltf_vrm_firstperson_degreemap_free(memory, &data->lookAtHorizontalOuter);
	cgltf_vrm_firstperson_degreemap_free(memory, &data->lookAtVerticalDown);
	cgltf_vrm_firstperson_degreemap_free(memory, &data->lookAtVerticalUp);
}
static void cgltf_vrm_humanoid_bone_free(const struct cgltf_memory_options* memory, cgltf_vrm_humanoid_bone* data) {
	memory->free(memory->user_data, data->min);
	memory->free(memory->user_data, data->max);
	memory->free(memory->user_data, data->center);
}
static void cgltf_vrm_humanoid_free(const struct cgltf_memory_options* memory, cgltf_vrm_humanoid* data) {
	for (cgltf_size i = 0; i < data->humanBones_count; i++) {
		cgltf_vrm_humanoid_bone_free(memory, &data->humanBones[i]);
	}
	memory->free(memory->user_data, data->humanBones);
}
static void cgltf_vrm_material_free(const struct cgltf_memory_options* memory, cgltf_vrm_material* data) {
	memory->free(memory->user_data, data->name);
	memory->free(memory->user_data, data->shader);
	for (cgltf_size i = 0; i < data->floatProperties_count; i++) {
		memory->free(memory->user_data, data->floatProperties_keys[i]);
	}
	memory->free(memory->user_data, data->floatProperties_keys);
	memory->free(memory->user_data, data->floatProperties_values);
	for (cgltf_size i = 0; i < data->vectorProperties_count; i++) {
		memory->free(memory->user_data, data->vectorProperties_keys[i]);
		memory->free(memory->user_data, data->vectorProperties_values[i]);
	}
	memory->free(memory->user_data, data->vectorProperties_keys);
	memory->free(memory->user_data, data->vectorProperties_values);
	for (cgltf_size i = 0; i < data->textureProperties_count; i++) {
		memory->free(memory->user_data, data->textureProperties_keys[i]);
	}
	memory->free(memory->user_data, data->textureProperties_keys);
	memory->free(memory->user_data, data->textureProperties_values);
	for (cgltf_size i = 0; i < data->keywordMap_count; i++) {
		memory->free(memory->user_data, data->keywordMap_keys[i]);
	}
	memory->free(memory->user_data, data->keywordMap_keys);
	memory->free(memory->user_data, data->keywordMap_values);
	for (cgltf_size i = 0; i < data->tagMap_count; i++) {
		memory->free(memory->user_data, data->tagMap_keys[i]);
		memory->free(memory->user_data, data->tagMap_values[i]);
	}
	memory->free(memory->user_data, data->tagMap_keys);
	memory->free(memory->user_data, data->tagMap_values);
}
static void cgltf_vrm_meta_free(const struct cgltf_memory_options* memory, cgltf_vrm_meta* data) {
	memory->free(memory->user_data, data->title);
	memory->free(memory->user_data, data->version);
	memory->free(memory->user_data, data->author);
	memory->free(memory->user_data, data->contactInformation);
	memory->free(memory->user_data, data->reference);
	memory->free(memory->user_data, data->otherPermissionUrl);
	memory->free(memory->user_data, data->otherLicenseUrl);
}
static void cgltf_vrm_free(const struct cgltf_memory_options* memory, cgltf_vrm* data) {
	memory->free(memory->user_data, data->exporterVersion);
	memory->free(memory->user_data, data->specVersion);
	cgltf_vrm_meta_free(memory, &data->meta);
	cgltf_vrm_humanoid_free(memory, &data->humanoid);
	cgltf_vrm_firstperson_free(memory, &data->firstPerson);
	cgltf_vrm_blendshape_free(memory, &data->blendShapeMaster);
	cgltf_vrm_secondaryanimation_free(memory, &data->secondaryAnimation);
	for (cgltf_size i = 0; i < data->materialProperties_count; i++) {
		cgltf_vrm_material_free(memory, &data->materialProperties[i]);
	}
	memory->free(memory->user_data, data->materialProperties);
}static cgltf_bool select_cgltf_vrm_blendshape_group_presetName(const char* name, cgltf_vrm_blendshape_group_presetName* out) {
	if (strlen(name) == 0) {
		return 0;
	} else if (strncmp(name, "unknown", 7) == 0) {
		*out = cgltf_vrm_blendshape_group_presetName_unknown;
		return 1;
	} else if (strncmp(name, "neutral", 7) == 0) {
		*out = cgltf_vrm_blendshape_group_presetName_neutral;
		return 1;
	} else if (strncmp(name, "a", 1) == 0) {
		*out = cgltf_vrm_blendshape_group_presetName_a;
		return 1;
	} else if (strncmp(name, "i", 1) == 0) {
		*out = cgltf_vrm_blendshape_group_presetName_i;
		return 1;
	} else if (strncmp(name, "u", 1) == 0) {
		*out = cgltf_vrm_blendshape_group_presetName_u;
		return 1;
	} else if (strncmp(name, "e", 1) == 0) {
		*out = cgltf_vrm_blendshape_group_presetName_e;
		return 1;
	} else if (strncmp(name, "o", 1) == 0) {
		*out = cgltf_vrm_blendshape_group_presetName_o;
		return 1;
	} else if (strncmp(name, "blink", 5) == 0) {
		*out = cgltf_vrm_blendshape_group_presetName_blink;
		return 1;
	} else if (strncmp(name, "joy", 3) == 0) {
		*out = cgltf_vrm_blendshape_group_presetName_joy;
		return 1;
	} else if (strncmp(name, "angry", 5) == 0) {
		*out = cgltf_vrm_blendshape_group_presetName_angry;
		return 1;
	} else if (strncmp(name, "sorrow", 6) == 0) {
		*out = cgltf_vrm_blendshape_group_presetName_sorrow;
		return 1;
	} else if (strncmp(name, "fun", 3) == 0) {
		*out = cgltf_vrm_blendshape_group_presetName_fun;
		return 1;
	} else if (strncmp(name, "lookup", 6) == 0) {
		*out = cgltf_vrm_blendshape_group_presetName_lookup;
		return 1;
	} else if (strncmp(name, "lookdown", 8) == 0) {
		*out = cgltf_vrm_blendshape_group_presetName_lookdown;
		return 1;
	} else if (strncmp(name, "lookleft", 8) == 0) {
		*out = cgltf_vrm_blendshape_group_presetName_lookleft;
		return 1;
	} else if (strncmp(name, "lookright", 9) == 0) {
		*out = cgltf_vrm_blendshape_group_presetName_lookright;
		return 1;
	} else if (strncmp(name, "blink_l", 7) == 0) {
		*out = cgltf_vrm_blendshape_group_presetName_blink_l;
		return 1;
	} else if (strncmp(name, "blink_r", 7) == 0) {
		*out = cgltf_vrm_blendshape_group_presetName_blink_r;
		return 1;
	}
		return 0;
}

static cgltf_bool select_cgltf_vrm_firstperson_lookAtTypeName(const char* name, cgltf_vrm_firstperson_lookAtTypeName* out) {
	if (strlen(name) == 0) {
		return 0;
	} else if (strncmp(name, "Bone", 4) == 0) {
		*out = cgltf_vrm_firstperson_lookAtTypeName_Bone;
		return 1;
	} else if (strncmp(name, "BlendShape", 10) == 0) {
		*out = cgltf_vrm_firstperson_lookAtTypeName_BlendShape;
		return 1;
	}
		return 0;
}

static cgltf_bool select_cgltf_vrm_humanoid_bone_bone(const char* name, cgltf_vrm_humanoid_bone_bone* out) {
	if (strlen(name) == 0) {
		return 0;
	} else if (strncmp(name, "hips", 4) == 0) {
		*out = cgltf_vrm_humanoid_bone_bone_hips;
		return 1;
	} else if (strncmp(name, "leftUpperLeg", 12) == 0) {
		*out = cgltf_vrm_humanoid_bone_bone_leftUpperLeg;
		return 1;
	} else if (strncmp(name, "rightUpperLeg", 13) == 0) {
		*out = cgltf_vrm_humanoid_bone_bone_rightUpperLeg;
		return 1;
	} else if (strncmp(name, "leftLowerLeg", 12) == 0) {
		*out = cgltf_vrm_humanoid_bone_bone_leftLowerLeg;
		return 1;
	} else if (strncmp(name, "rightLowerLeg", 13) == 0) {
		*out = cgltf_vrm_humanoid_bone_bone_rightLowerLeg;
		return 1;
	} else if (strncmp(name, "leftFoot", 8) == 0) {
		*out = cgltf_vrm_humanoid_bone_bone_leftFoot;
		return 1;
	} else if (strncmp(name, "rightFoot", 9) == 0) {
		*out = cgltf_vrm_humanoid_bone_bone_rightFoot;
		return 1;
	} else if (strncmp(name, "spine", 5) == 0) {
		*out = cgltf_vrm_humanoid_bone_bone_spine;
		return 1;
	} else if (strncmp(name, "chest", 5) == 0) {
		*out = cgltf_vrm_humanoid_bone_bone_chest;
		return 1;
	} else if (strncmp(name, "neck", 4) == 0) {
		*out = cgltf_vrm_humanoid_bone_bone_neck;
		return 1;
	} else if (strncmp(name, "head", 4) == 0) {
		*out = cgltf_vrm_humanoid_bone_bone_head;
		return 1;
	} else if (strncmp(name, "leftShoulder", 12) == 0) {
		*out = cgltf_vrm_humanoid_bone_bone_leftShoulder;
		return 1;
	} else if (strncmp(name, "rightShoulder", 13) == 0) {
		*out = cgltf_vrm_humanoid_bone_bone_rightShoulder;
		return 1;
	} else if (strncmp(name, "leftUpperArm", 12) == 0) {
		*out = cgltf_vrm_humanoid_bone_bone_leftUpperArm;
		return 1;
	} else if (strncmp(name, "rightUpperArm", 13) == 0) {
		*out = cgltf_vrm_humanoid_bone_bone_rightUpperArm;
		return 1;
	} else if (strncmp(name, "leftLowerArm", 12) == 0) {
		*out = cgltf_vrm_humanoid_bone_bone_leftLowerArm;
		return 1;
	} else if (strncmp(name, "rightLowerArm", 13) == 0) {
		*out = cgltf_vrm_humanoid_bone_bone_rightLowerArm;
		return 1;
	} else if (strncmp(name, "leftHand", 8) == 0) {
		*out = cgltf_vrm_humanoid_bone_bone_leftHand;
		return 1;
	} else if (strncmp(name, "rightHand", 9) == 0) {
		*out = cgltf_vrm_humanoid_bone_bone_rightHand;
		return 1;
	} else if (strncmp(name, "leftToes", 8) == 0) {
		*out = cgltf_vrm_humanoid_bone_bone_leftToes;
		return 1;
	} else if (strncmp(name, "rightToes", 9) == 0) {
		*out = cgltf_vrm_humanoid_bone_bone_rightToes;
		return 1;
	} else if (strncmp(name, "leftEye", 7) == 0) {
		*out = cgltf_vrm_humanoid_bone_bone_leftEye;
		return 1;
	} else if (strncmp(name, "rightEye", 8) == 0) {
		*out = cgltf_vrm_humanoid_bone_bone_rightEye;
		return 1;
	} else if (strncmp(name, "jaw", 3) == 0) {
		*out = cgltf_vrm_humanoid_bone_bone_jaw;
		return 1;
	} else if (strncmp(name, "leftThumbProximal", 17) == 0) {
		*out = cgltf_vrm_humanoid_bone_bone_leftThumbProximal;
		return 1;
	} else if (strncmp(name, "leftThumbIntermediate", 21) == 0) {
		*out = cgltf_vrm_humanoid_bone_bone_leftThumbIntermediate;
		return 1;
	} else if (strncmp(name, "leftThumbDistal", 15) == 0) {
		*out = cgltf_vrm_humanoid_bone_bone_leftThumbDistal;
		return 1;
	} else if (strncmp(name, "leftIndexProximal", 17) == 0) {
		*out = cgltf_vrm_humanoid_bone_bone_leftIndexProximal;
		return 1;
	} else if (strncmp(name, "leftIndexIntermediate", 21) == 0) {
		*out = cgltf_vrm_humanoid_bone_bone_leftIndexIntermediate;
		return 1;
	} else if (strncmp(name, "leftIndexDistal", 15) == 0) {
		*out = cgltf_vrm_humanoid_bone_bone_leftIndexDistal;
		return 1;
	} else if (strncmp(name, "leftMiddleProximal", 18) == 0) {
		*out = cgltf_vrm_humanoid_bone_bone_leftMiddleProximal;
		return 1;
	} else if (strncmp(name, "leftMiddleIntermediate", 22) == 0) {
		*out = cgltf_vrm_humanoid_bone_bone_leftMiddleIntermediate;
		return 1;
	} else if (strncmp(name, "leftMiddleDistal", 16) == 0) {
		*out = cgltf_vrm_humanoid_bone_bone_leftMiddleDistal;
		return 1;
	} else if (strncmp(name, "leftRingProximal", 16) == 0) {
		*out = cgltf_vrm_humanoid_bone_bone_leftRingProximal;
		return 1;
	} else if (strncmp(name, "leftRingIntermediate", 20) == 0) {
		*out = cgltf_vrm_humanoid_bone_bone_leftRingIntermediate;
		return 1;
	} else if (strncmp(name, "leftRingDistal", 14) == 0) {
		*out = cgltf_vrm_humanoid_bone_bone_leftRingDistal;
		return 1;
	} else if (strncmp(name, "leftLittleProximal", 18) == 0) {
		*out = cgltf_vrm_humanoid_bone_bone_leftLittleProximal;
		return 1;
	} else if (strncmp(name, "leftLittleIntermediate", 22) == 0) {
		*out = cgltf_vrm_humanoid_bone_bone_leftLittleIntermediate;
		return 1;
	} else if (strncmp(name, "leftLittleDistal", 16) == 0) {
		*out = cgltf_vrm_humanoid_bone_bone_leftLittleDistal;
		return 1;
	} else if (strncmp(name, "rightThumbProximal", 18) == 0) {
		*out = cgltf_vrm_humanoid_bone_bone_rightThumbProximal;
		return 1;
	} else if (strncmp(name, "rightThumbIntermediate", 22) == 0) {
		*out = cgltf_vrm_humanoid_bone_bone_rightThumbIntermediate;
		return 1;
	} else if (strncmp(name, "rightThumbDistal", 16) == 0) {
		*out = cgltf_vrm_humanoid_bone_bone_rightThumbDistal;
		return 1;
	} else if (strncmp(name, "rightIndexProximal", 18) == 0) {
		*out = cgltf_vrm_humanoid_bone_bone_rightIndexProximal;
		return 1;
	} else if (strncmp(name, "rightIndexIntermediate", 22) == 0) {
		*out = cgltf_vrm_humanoid_bone_bone_rightIndexIntermediate;
		return 1;
	} else if (strncmp(name, "rightIndexDistal", 16) == 0) {
		*out = cgltf_vrm_humanoid_bone_bone_rightIndexDistal;
		return 1;
	} else if (strncmp(name, "rightMiddleProximal", 19) == 0) {
		*out = cgltf_vrm_humanoid_bone_bone_rightMiddleProximal;
		return 1;
	} else if (strncmp(name, "rightMiddleIntermediate", 23) == 0) {
		*out = cgltf_vrm_humanoid_bone_bone_rightMiddleIntermediate;
		return 1;
	} else if (strncmp(name, "rightMiddleDistal", 17) == 0) {
		*out = cgltf_vrm_humanoid_bone_bone_rightMiddleDistal;
		return 1;
	} else if (strncmp(name, "rightRingProximal", 17) == 0) {
		*out = cgltf_vrm_humanoid_bone_bone_rightRingProximal;
		return 1;
	} else if (strncmp(name, "rightRingIntermediate", 21) == 0) {
		*out = cgltf_vrm_humanoid_bone_bone_rightRingIntermediate;
		return 1;
	} else if (strncmp(name, "rightRingDistal", 15) == 0) {
		*out = cgltf_vrm_humanoid_bone_bone_rightRingDistal;
		return 1;
	} else if (strncmp(name, "rightLittleProximal", 19) == 0) {
		*out = cgltf_vrm_humanoid_bone_bone_rightLittleProximal;
		return 1;
	} else if (strncmp(name, "rightLittleIntermediate", 23) == 0) {
		*out = cgltf_vrm_humanoid_bone_bone_rightLittleIntermediate;
		return 1;
	} else if (strncmp(name, "rightLittleDistal", 17) == 0) {
		*out = cgltf_vrm_humanoid_bone_bone_rightLittleDistal;
		return 1;
	} else if (strncmp(name, "upperChest", 10) == 0) {
		*out = cgltf_vrm_humanoid_bone_bone_upperChest;
		return 1;
	}
		return 0;
}

static cgltf_bool select_cgltf_vrm_meta_allowedUserName(const char* name, cgltf_vrm_meta_allowedUserName* out) {
	if (strlen(name) == 0) {
		return 0;
	} else if (strncmp(name, "OnlyAuthor", 10) == 0) {
		*out = cgltf_vrm_meta_allowedUserName_OnlyAuthor;
		return 1;
	} else if (strncmp(name, "ExplicitlyLicensedPerson", 24) == 0) {
		*out = cgltf_vrm_meta_allowedUserName_ExplicitlyLicensedPerson;
		return 1;
	} else if (strncmp(name, "Everyone", 8) == 0) {
		*out = cgltf_vrm_meta_allowedUserName_Everyone;
		return 1;
	}
		return 0;
}

static cgltf_bool select_cgltf_vrm_meta_violentUssageName(const char* name, cgltf_vrm_meta_violentUssageName* out) {
	if (strlen(name) == 0) {
		return 0;
	} else if (strncmp(name, "Disallow", 8) == 0) {
		*out = cgltf_vrm_meta_violentUssageName_Disallow;
		return 1;
	} else if (strncmp(name, "Allow", 5) == 0) {
		*out = cgltf_vrm_meta_violentUssageName_Allow;
		return 1;
	}
		return 0;
}

static cgltf_bool select_cgltf_vrm_meta_sexualUssageName(const char* name, cgltf_vrm_meta_sexualUssageName* out) {
	if (strlen(name) == 0) {
		return 0;
	} else if (strncmp(name, "Disallow", 8) == 0) {
		*out = cgltf_vrm_meta_sexualUssageName_Disallow;
		return 1;
	} else if (strncmp(name, "Allow", 5) == 0) {
		*out = cgltf_vrm_meta_sexualUssageName_Allow;
		return 1;
	}
		return 0;
}

static cgltf_bool select_cgltf_vrm_meta_commercialUssageName(const char* name, cgltf_vrm_meta_commercialUssageName* out) {
	if (strlen(name) == 0) {
		return 0;
	} else if (strncmp(name, "Disallow", 8) == 0) {
		*out = cgltf_vrm_meta_commercialUssageName_Disallow;
		return 1;
	} else if (strncmp(name, "Allow", 5) == 0) {
		*out = cgltf_vrm_meta_commercialUssageName_Allow;
		return 1;
	}
		return 0;
}

static cgltf_bool select_cgltf_vrm_meta_licenseName(const char* name, cgltf_vrm_meta_licenseName* out) {
	if (strlen(name) == 0) {
		return 0;
	} else if (strncmp(name, "Redistribution_Prohibited", 25) == 0) {
		*out = cgltf_vrm_meta_licenseName_Redistribution_Prohibited;
		return 1;
	} else if (strncmp(name, "CC0", 3) == 0) {
		*out = cgltf_vrm_meta_licenseName_CC0;
		return 1;
	} else if (strncmp(name, "CC_BY", 5) == 0) {
		*out = cgltf_vrm_meta_licenseName_CC_BY;
		return 1;
	} else if (strncmp(name, "CC_BY_NC", 8) == 0) {
		*out = cgltf_vrm_meta_licenseName_CC_BY_NC;
		return 1;
	} else if (strncmp(name, "CC_BY_SA", 8) == 0) {
		*out = cgltf_vrm_meta_licenseName_CC_BY_SA;
		return 1;
	} else if (strncmp(name, "CC_BY_NC_SA", 11) == 0) {
		*out = cgltf_vrm_meta_licenseName_CC_BY_NC_SA;
		return 1;
	} else if (strncmp(name, "CC_BY_ND", 8) == 0) {
		*out = cgltf_vrm_meta_licenseName_CC_BY_ND;
		return 1;
	} else if (strncmp(name, "CC_BY_NC_ND", 11) == 0) {
		*out = cgltf_vrm_meta_licenseName_CC_BY_NC_ND;
		return 1;
	} else if (strncmp(name, "Other", 5) == 0) {
		*out = cgltf_vrm_meta_licenseName_Other;
		return 1;
	}
		return 0;
}
static int cgltf_parse_json_vrm_secondaryanimation_collidergroup_colliders(cgltf_options* options, jsmntok_t const* tokens, int i, const uint8_t* json_chunk, cgltf_vrm_secondaryanimation_collidergroup_colliders* out_data) {
	if (tokens[i].type == JSMN_OBJECT) {
		int size = tokens[i].size; ++i;
		for (int j = 0; j < size; ++j) {
			if (tokens[i].type != JSMN_STRING || tokens[i].size == 0) {
				continue;
			} else {
				i = cgltf_skip_json(tokens, i + 1);
			}
			if (i < 0) return i;
		}
	} else {
		i = cgltf_skip_json(tokens, i + 1);
	}
	return i;
}
static int cgltf_parse_json_vrm_secondaryanimation_spring(cgltf_options* options, jsmntok_t const* tokens, int i, const uint8_t* json_chunk, cgltf_vrm_secondaryanimation_spring* out_data) {
	if (tokens[i].type == JSMN_OBJECT) {
		int size = tokens[i].size; ++i;
		for (int j = 0; j < size; ++j) {
			if (tokens[i].type != JSMN_STRING || tokens[i].size == 0) {
				continue;
			} else if (cgltf_json_strcmp(tokens + i, json_chunk, "comment") == 0) {
				i = cgltf_parse_json_string(options, tokens, i + 1, json_chunk, &out_data->comment);
			} else {
				i = cgltf_skip_json(tokens, i + 1);
			}
			if (i < 0) return i;
		}
	} else {
		i = cgltf_skip_json(tokens, i + 1);
	}
	return i;
}
static int cgltf_parse_json_vrm_secondaryanimation_collidergroup(cgltf_options* options, jsmntok_t const* tokens, int i, const uint8_t* json_chunk, cgltf_vrm_secondaryanimation_collidergroup* out_data) {
	if (tokens[i].type == JSMN_OBJECT) {
		int size = tokens[i].size; ++i;
		for (int j = 0; j < size; ++j) {
			if (tokens[i].type != JSMN_STRING || tokens[i].size == 0) {
				continue;
			} else {
				i = cgltf_skip_json(tokens, i + 1);
			}
			if (i < 0) return i;
		}
	} else {
		i = cgltf_skip_json(tokens, i + 1);
	}
	return i;
}
static int cgltf_parse_json_vrm_secondaryanimation(cgltf_options* options, jsmntok_t const* tokens, int i, const uint8_t* json_chunk, cgltf_vrm_secondaryanimation* out_data) {
	if (tokens[i].type == JSMN_OBJECT) {
		int size = tokens[i].size; ++i;
		for (int j = 0; j < size; ++j) {
			if (tokens[i].type != JSMN_STRING || tokens[i].size == 0) {
				continue;
			} else {
				i = cgltf_skip_json(tokens, i + 1);
			}
			if (i < 0) return i;
		}
	} else {
		i = cgltf_skip_json(tokens, i + 1);
	}
	return i;
}
static int cgltf_parse_json_vrm_blendshape_bind(cgltf_options* options, jsmntok_t const* tokens, int i, const uint8_t* json_chunk, cgltf_vrm_blendshape_bind* out_data) {
	if (tokens[i].type == JSMN_OBJECT) {
		int size = tokens[i].size; ++i;
		for (int j = 0; j < size; ++j) {
			if (tokens[i].type != JSMN_STRING || tokens[i].size == 0) {
				continue;
			} else {
				i = cgltf_skip_json(tokens, i + 1);
			}
			if (i < 0) return i;
		}
	} else {
		i = cgltf_skip_json(tokens, i + 1);
	}
	return i;
}
static int cgltf_parse_json_vrm_blendshape_materialbind(cgltf_options* options, jsmntok_t const* tokens, int i, const uint8_t* json_chunk, cgltf_vrm_blendshape_materialbind* out_data) {
	if (tokens[i].type == JSMN_OBJECT) {
		int size = tokens[i].size; ++i;
		for (int j = 0; j < size; ++j) {
			if (tokens[i].type != JSMN_STRING || tokens[i].size == 0) {
				continue;
			} else if (cgltf_json_strcmp(tokens + i, json_chunk, "materialName") == 0) {
				i = cgltf_parse_json_string(options, tokens, i + 1, json_chunk, &out_data->materialName);
			} else if (cgltf_json_strcmp(tokens + i, json_chunk, "propertyName") == 0) {
				i = cgltf_parse_json_string(options, tokens, i + 1, json_chunk, &out_data->propertyName);
			} else {
				i = cgltf_skip_json(tokens, i + 1);
			}
			if (i < 0) return i;
		}
	} else {
		i = cgltf_skip_json(tokens, i + 1);
	}
	return i;
}
static int cgltf_parse_json_vrm_blendshape_group(cgltf_options* options, jsmntok_t const* tokens, int i, const uint8_t* json_chunk, cgltf_vrm_blendshape_group* out_data) {
	if (tokens[i].type == JSMN_OBJECT) {
		int size = tokens[i].size; ++i;
		for (int j = 0; j < size; ++j) {
			if (tokens[i].type != JSMN_STRING || tokens[i].size == 0) {
				continue;
			} else if (cgltf_json_strcmp(tokens + i, json_chunk, "name") == 0) {
				i = cgltf_parse_json_string(options, tokens, i + 1, json_chunk, &out_data->name);
			} else {
				i = cgltf_skip_json(tokens, i + 1);
			}
			if (i < 0) return i;
		}
	} else {
		i = cgltf_skip_json(tokens, i + 1);
	}
	return i;
}
static int cgltf_parse_json_vrm_blendshape(cgltf_options* options, jsmntok_t const* tokens, int i, const uint8_t* json_chunk, cgltf_vrm_blendshape* out_data) {
	if (tokens[i].type == JSMN_OBJECT) {
		int size = tokens[i].size; ++i;
		for (int j = 0; j < size; ++j) {
			if (tokens[i].type != JSMN_STRING || tokens[i].size == 0) {
				continue;
			} else {
				i = cgltf_skip_json(tokens, i + 1);
			}
			if (i < 0) return i;
		}
	} else {
		i = cgltf_skip_json(tokens, i + 1);
	}
	return i;
}
static int cgltf_parse_json_vrm_firstperson_degreemap(cgltf_options* options, jsmntok_t const* tokens, int i, const uint8_t* json_chunk, cgltf_vrm_firstperson_degreemap* out_data) {
	if (tokens[i].type == JSMN_OBJECT) {
		int size = tokens[i].size; ++i;
		for (int j = 0; j < size; ++j) {
			if (tokens[i].type != JSMN_STRING || tokens[i].size == 0) {
				continue;
			} else {
				i = cgltf_skip_json(tokens, i + 1);
			}
			if (i < 0) return i;
		}
	} else {
		i = cgltf_skip_json(tokens, i + 1);
	}
	return i;
}
static int cgltf_parse_json_vrm_firstperson_meshannotation(cgltf_options* options, jsmntok_t const* tokens, int i, const uint8_t* json_chunk, cgltf_vrm_firstperson_meshannotation* out_data) {
	if (tokens[i].type == JSMN_OBJECT) {
		int size = tokens[i].size; ++i;
		for (int j = 0; j < size; ++j) {
			if (tokens[i].type != JSMN_STRING || tokens[i].size == 0) {
				continue;
			} else if (cgltf_json_strcmp(tokens + i, json_chunk, "firstPersonFlag") == 0) {
				i = cgltf_parse_json_string(options, tokens, i + 1, json_chunk, &out_data->firstPersonFlag);
			} else {
				i = cgltf_skip_json(tokens, i + 1);
			}
			if (i < 0) return i;
		}
	} else {
		i = cgltf_skip_json(tokens, i + 1);
	}
	return i;
}
static int cgltf_parse_json_vrm_firstperson(cgltf_options* options, jsmntok_t const* tokens, int i, const uint8_t* json_chunk, cgltf_vrm_firstperson* out_data) {
	if (tokens[i].type == JSMN_OBJECT) {
		int size = tokens[i].size; ++i;
		for (int j = 0; j < size; ++j) {
			if (tokens[i].type != JSMN_STRING || tokens[i].size == 0) {
				continue;
			} else {
				i = cgltf_skip_json(tokens, i + 1);
			}
			if (i < 0) return i;
		}
	} else {
		i = cgltf_skip_json(tokens, i + 1);
	}
	return i;
}
static int cgltf_parse_json_vrm_humanoid_bone(cgltf_options* options, jsmntok_t const* tokens, int i, const uint8_t* json_chunk, cgltf_vrm_humanoid_bone* out_data) {
	if (tokens[i].type == JSMN_OBJECT) {
		int size = tokens[i].size; ++i;
		for (int j = 0; j < size; ++j) {
			if (tokens[i].type != JSMN_STRING || tokens[i].size == 0) {
				continue;
			} else {
				i = cgltf_skip_json(tokens, i + 1);
			}
			if (i < 0) return i;
		}
	} else {
		i = cgltf_skip_json(tokens, i + 1);
	}
	return i;
}
static int cgltf_parse_json_vrm_humanoid(cgltf_options* options, jsmntok_t const* tokens, int i, const uint8_t* json_chunk, cgltf_vrm_humanoid* out_data) {
	if (tokens[i].type == JSMN_OBJECT) {
		int size = tokens[i].size; ++i;
		for (int j = 0; j < size; ++j) {
			if (tokens[i].type != JSMN_STRING || tokens[i].size == 0) {
				continue;
			} else {
				i = cgltf_skip_json(tokens, i + 1);
			}
			if (i < 0) return i;
		}
	} else {
		i = cgltf_skip_json(tokens, i + 1);
	}
	return i;
}
static int cgltf_parse_json_vrm_material(cgltf_options* options, jsmntok_t const* tokens, int i, const uint8_t* json_chunk, cgltf_vrm_material* out_data) {
	if (tokens[i].type == JSMN_OBJECT) {
		int size = tokens[i].size; ++i;
		for (int j = 0; j < size; ++j) {
			if (tokens[i].type != JSMN_STRING || tokens[i].size == 0) {
				continue;
			} else if (cgltf_json_strcmp(tokens + i, json_chunk, "name") == 0) {
				i = cgltf_parse_json_string(options, tokens, i + 1, json_chunk, &out_data->name);
			} else if (cgltf_json_strcmp(tokens + i, json_chunk, "shader") == 0) {
				i = cgltf_parse_json_string(options, tokens, i + 1, json_chunk, &out_data->shader);
			} else {
				i = cgltf_skip_json(tokens, i + 1);
			}
			if (i < 0) return i;
		}
	} else {
		i = cgltf_skip_json(tokens, i + 1);
	}
	return i;
}
static int cgltf_parse_json_vrm_meta(cgltf_options* options, jsmntok_t const* tokens, int i, const uint8_t* json_chunk, cgltf_vrm_meta* out_data) {
	if (tokens[i].type == JSMN_OBJECT) {
		int size = tokens[i].size; ++i;
		for (int j = 0; j < size; ++j) {
			if (tokens[i].type != JSMN_STRING || tokens[i].size == 0) {
				continue;
			} else if (cgltf_json_strcmp(tokens + i, json_chunk, "title") == 0) {
				i = cgltf_parse_json_string(options, tokens, i + 1, json_chunk, &out_data->title);
			} else if (cgltf_json_strcmp(tokens + i, json_chunk, "version") == 0) {
				i = cgltf_parse_json_string(options, tokens, i + 1, json_chunk, &out_data->version);
			} else if (cgltf_json_strcmp(tokens + i, json_chunk, "author") == 0) {
				i = cgltf_parse_json_string(options, tokens, i + 1, json_chunk, &out_data->author);
			} else if (cgltf_json_strcmp(tokens + i, json_chunk, "contactInformation") == 0) {
				i = cgltf_parse_json_string(options, tokens, i + 1, json_chunk, &out_data->contactInformation);
			} else if (cgltf_json_strcmp(tokens + i, json_chunk, "reference") == 0) {
				i = cgltf_parse_json_string(options, tokens, i + 1, json_chunk, &out_data->reference);
			} else if (cgltf_json_strcmp(tokens + i, json_chunk, "otherPermissionUrl") == 0) {
				i = cgltf_parse_json_string(options, tokens, i + 1, json_chunk, &out_data->otherPermissionUrl);
			} else if (cgltf_json_strcmp(tokens + i, json_chunk, "otherLicenseUrl") == 0) {
				i = cgltf_parse_json_string(options, tokens, i + 1, json_chunk, &out_data->otherLicenseUrl);
			} else {
				i = cgltf_skip_json(tokens, i + 1);
			}
			if (i < 0) return i;
		}
	} else {
		i = cgltf_skip_json(tokens, i + 1);
	}
	return i;
}
static int cgltf_parse_json_vrm(cgltf_options* options, jsmntok_t const* tokens, int i, const uint8_t* json_chunk, cgltf_vrm* out_data) {
	if (tokens[i].type == JSMN_OBJECT) {
		int size = tokens[i].size; ++i;
		for (int j = 0; j < size; ++j) {
			if (tokens[i].type != JSMN_STRING || tokens[i].size == 0) {
				continue;
			} else if (cgltf_json_strcmp(tokens + i, json_chunk, "exporterVersion") == 0) {
				i = cgltf_parse_json_string(options, tokens, i + 1, json_chunk, &out_data->exporterVersion);
			} else if (cgltf_json_strcmp(tokens + i, json_chunk, "specVersion") == 0) {
				i = cgltf_parse_json_string(options, tokens, i + 1, json_chunk, &out_data->specVersion);
			} else {
				i = cgltf_skip_json(tokens, i + 1);
			}
			if (i < 0) return i;
		}
	} else {
		i = cgltf_skip_json(tokens, i + 1);
	}
	return i;
}