static void cgltf_vrmc_vrm_springbone_collidergroup_collider_v1_0_free(const struct cgltf_memory_options* memory, cgltf_vrmc_vrm_springbone_collidergroup_collider_v1_0* data) {
	memory->free(memory->user_data, data->offset);
}

static void cgltf_vrmc_vrm_springbone_bonegroup_v1_0_free(const struct cgltf_memory_options* memory, cgltf_vrmc_vrm_springbone_bonegroup_v1_0* data) {
	memory->free(memory->user_data, data->name);
	memory->free(memory->user_data, data->gravityDir);
	memory->free(memory->user_data, data->bones);
	memory->free(memory->user_data, data->colliderGroups);
}

static void cgltf_vrmc_vrm_springbone_collidergroup_v1_0_free(const struct cgltf_memory_options* memory, cgltf_vrmc_vrm_springbone_collidergroup_v1_0* data) {
	for (cgltf_size i = 0; i < data->colliders_count; i++) {
		cgltf_vrmc_vrm_springbone_collidergroup_collider_v1_0_free(memory, &data->colliders[i]);
	}
	memory->free(memory->user_data, data->colliders);
}

static void cgltf_vrmc_vrm_springbone_v1_0_free(const struct cgltf_memory_options* memory, cgltf_vrmc_vrm_springbone_v1_0* data) {
	for (cgltf_size i = 0; i < data->boneGroups_count; i++) {
		cgltf_vrmc_vrm_springbone_bonegroup_v1_0_free(memory, &data->boneGroups[i]);
	}
	memory->free(memory->user_data, data->boneGroups);
	for (cgltf_size i = 0; i < data->colliderGroups_count; i++) {
		cgltf_vrmc_vrm_springbone_collidergroup_v1_0_free(memory, &data->colliderGroups[i]);
	}
	memory->free(memory->user_data, data->colliderGroups);
}

static void cgltf_vrmc_vrm_blendshape_blendshapegroup_blendshapebind_v1_0_free(const struct cgltf_memory_options* memory, cgltf_vrmc_vrm_blendshape_blendshapegroup_blendshapebind_v1_0* data) {
	memory->free(memory->user_data, data->node);
	memory->free(memory->user_data, data->index);
}

static void cgltf_vrmc_vrm_blendshape_blendshapegroup_materialuvbind_v1_0_free(const struct cgltf_memory_options* memory, cgltf_vrmc_vrm_blendshape_blendshapegroup_materialuvbind_v1_0* data) {
	memory->free(memory->user_data, data->scaling);
	memory->free(memory->user_data, data->offset);
}

static void cgltf_vrmc_vrm_blendshape_blendshapegroup_materialvalue_v1_0_free(const struct cgltf_memory_options* memory, cgltf_vrmc_vrm_blendshape_blendshapegroup_materialvalue_v1_0* data) {
	memory->free(memory->user_data, data->targetValue);
}

static void cgltf_vrmc_vrm_blendshape_blendshapegroup_v1_0_free(const struct cgltf_memory_options* memory, cgltf_vrmc_vrm_blendshape_blendshapegroup_v1_0* data) {
	memory->free(memory->user_data, data->name);
	for (cgltf_size i = 0; i < data->binds_count; i++) {
		cgltf_vrmc_vrm_blendshape_blendshapegroup_blendshapebind_v1_0_free(memory, &data->binds[i]);
	}
	memory->free(memory->user_data, data->binds);
	for (cgltf_size i = 0; i < data->materialValues_count; i++) {
		cgltf_vrmc_vrm_blendshape_blendshapegroup_materialvalue_v1_0_free(memory, &data->materialValues[i]);
	}
	memory->free(memory->user_data, data->materialValues);
	for (cgltf_size i = 0; i < data->materialUVBinds_count; i++) {
		cgltf_vrmc_vrm_blendshape_blendshapegroup_materialuvbind_v1_0_free(memory, &data->materialUVBinds[i]);
	}
	memory->free(memory->user_data, data->materialUVBinds);
}

static void cgltf_vrmc_vrm_blendshape_v1_0_free(const struct cgltf_memory_options* memory, cgltf_vrmc_vrm_blendshape_v1_0* data) {
	for (cgltf_size i = 0; i < data->blendShapeGroups_count; i++) {
		cgltf_vrmc_vrm_blendshape_blendshapegroup_v1_0_free(memory, &data->blendShapeGroups[i]);
	}
	memory->free(memory->user_data, data->blendShapeGroups);
}

static void cgltf_vrmc_vrm_constraint_v1_0_free(const struct cgltf_memory_options* memory, cgltf_vrmc_vrm_constraint_v1_0* data) {
	(void)memory;
	(void)data;
}

static void cgltf_vrmc_vrm_firstperson_meshannotation_v1_0_free(const struct cgltf_memory_options* memory, cgltf_vrmc_vrm_firstperson_meshannotation_v1_0* data) {
	memory->free(memory->user_data, data->node);
}

static void cgltf_vrmc_vrm_firstperson_v1_0_free(const struct cgltf_memory_options* memory, cgltf_vrmc_vrm_firstperson_v1_0* data) {
	for (cgltf_size i = 0; i < data->meshAnnotations_count; i++) {
		cgltf_vrmc_vrm_firstperson_meshannotation_v1_0_free(memory, &data->meshAnnotations[i]);
	}
	memory->free(memory->user_data, data->meshAnnotations);
}

static void cgltf_vrmc_vrm_humanoid_humanbones_humanbone_v1_0_free(const struct cgltf_memory_options* memory, cgltf_vrmc_vrm_humanoid_humanbones_humanbone_v1_0* data) {
	(void)memory;
	(void)data;
}

static void cgltf_vrmc_vrm_humanoid_humanbones_v1_0_free(const struct cgltf_memory_options* memory, cgltf_vrmc_vrm_humanoid_humanbones_v1_0* data) {
	cgltf_vrmc_vrm_humanoid_humanbones_humanbone_v1_0_free(memory, &data->hips);
	cgltf_vrmc_vrm_humanoid_humanbones_humanbone_v1_0_free(memory, &data->spine);
	cgltf_vrmc_vrm_humanoid_humanbones_humanbone_v1_0_free(memory, &data->chest);
	cgltf_vrmc_vrm_humanoid_humanbones_humanbone_v1_0_free(memory, &data->upperChest);
	cgltf_vrmc_vrm_humanoid_humanbones_humanbone_v1_0_free(memory, &data->neck);
	cgltf_vrmc_vrm_humanoid_humanbones_humanbone_v1_0_free(memory, &data->head);
	cgltf_vrmc_vrm_humanoid_humanbones_humanbone_v1_0_free(memory, &data->leftEye);
	cgltf_vrmc_vrm_humanoid_humanbones_humanbone_v1_0_free(memory, &data->rightEye);
	cgltf_vrmc_vrm_humanoid_humanbones_humanbone_v1_0_free(memory, &data->jaw);
	cgltf_vrmc_vrm_humanoid_humanbones_humanbone_v1_0_free(memory, &data->leftUpperLeg);
	cgltf_vrmc_vrm_humanoid_humanbones_humanbone_v1_0_free(memory, &data->leftLowerLeg);
	cgltf_vrmc_vrm_humanoid_humanbones_humanbone_v1_0_free(memory, &data->leftFoot);
	cgltf_vrmc_vrm_humanoid_humanbones_humanbone_v1_0_free(memory, &data->leftToes);
	cgltf_vrmc_vrm_humanoid_humanbones_humanbone_v1_0_free(memory, &data->rightUpperLeg);
	cgltf_vrmc_vrm_humanoid_humanbones_humanbone_v1_0_free(memory, &data->rightLowerLeg);
	cgltf_vrmc_vrm_humanoid_humanbones_humanbone_v1_0_free(memory, &data->rightFoot);
	cgltf_vrmc_vrm_humanoid_humanbones_humanbone_v1_0_free(memory, &data->rightToes);
	cgltf_vrmc_vrm_humanoid_humanbones_humanbone_v1_0_free(memory, &data->leftShoulder);
	cgltf_vrmc_vrm_humanoid_humanbones_humanbone_v1_0_free(memory, &data->leftUpperArm);
	cgltf_vrmc_vrm_humanoid_humanbones_humanbone_v1_0_free(memory, &data->leftLowerArm);
	cgltf_vrmc_vrm_humanoid_humanbones_humanbone_v1_0_free(memory, &data->leftHand);
	cgltf_vrmc_vrm_humanoid_humanbones_humanbone_v1_0_free(memory, &data->rightShoulder);
	cgltf_vrmc_vrm_humanoid_humanbones_humanbone_v1_0_free(memory, &data->rightUpperArm);
	cgltf_vrmc_vrm_humanoid_humanbones_humanbone_v1_0_free(memory, &data->rightLowerArm);
	cgltf_vrmc_vrm_humanoid_humanbones_humanbone_v1_0_free(memory, &data->rightHand);
	cgltf_vrmc_vrm_humanoid_humanbones_humanbone_v1_0_free(memory, &data->leftThumbProximal);
	cgltf_vrmc_vrm_humanoid_humanbones_humanbone_v1_0_free(memory, &data->leftThumbIntermediate);
	cgltf_vrmc_vrm_humanoid_humanbones_humanbone_v1_0_free(memory, &data->leftThumbDistal);
	cgltf_vrmc_vrm_humanoid_humanbones_humanbone_v1_0_free(memory, &data->leftIndexProximal);
	cgltf_vrmc_vrm_humanoid_humanbones_humanbone_v1_0_free(memory, &data->leftIndexIntermediate);
	cgltf_vrmc_vrm_humanoid_humanbones_humanbone_v1_0_free(memory, &data->leftIndexDistal);
	cgltf_vrmc_vrm_humanoid_humanbones_humanbone_v1_0_free(memory, &data->leftMiddleProximal);
	cgltf_vrmc_vrm_humanoid_humanbones_humanbone_v1_0_free(memory, &data->leftMiddleIntermediate);
	cgltf_vrmc_vrm_humanoid_humanbones_humanbone_v1_0_free(memory, &data->leftMiddleDistal);
	cgltf_vrmc_vrm_humanoid_humanbones_humanbone_v1_0_free(memory, &data->leftRingProximal);
	cgltf_vrmc_vrm_humanoid_humanbones_humanbone_v1_0_free(memory, &data->leftRingIntermediate);
	cgltf_vrmc_vrm_humanoid_humanbones_humanbone_v1_0_free(memory, &data->leftRingDistal);
	cgltf_vrmc_vrm_humanoid_humanbones_humanbone_v1_0_free(memory, &data->leftLittleProximal);
	cgltf_vrmc_vrm_humanoid_humanbones_humanbone_v1_0_free(memory, &data->leftLittleIntermediate);
	cgltf_vrmc_vrm_humanoid_humanbones_humanbone_v1_0_free(memory, &data->leftLittleDistal);
	cgltf_vrmc_vrm_humanoid_humanbones_humanbone_v1_0_free(memory, &data->rightThumbProximal);
	cgltf_vrmc_vrm_humanoid_humanbones_humanbone_v1_0_free(memory, &data->rightThumbIntermediate);
	cgltf_vrmc_vrm_humanoid_humanbones_humanbone_v1_0_free(memory, &data->rightThumbDistal);
	cgltf_vrmc_vrm_humanoid_humanbones_humanbone_v1_0_free(memory, &data->rightIndexProximal);
	cgltf_vrmc_vrm_humanoid_humanbones_humanbone_v1_0_free(memory, &data->rightIndexIntermediate);
	cgltf_vrmc_vrm_humanoid_humanbones_humanbone_v1_0_free(memory, &data->rightIndexDistal);
	cgltf_vrmc_vrm_humanoid_humanbones_humanbone_v1_0_free(memory, &data->rightMiddleProximal);
	cgltf_vrmc_vrm_humanoid_humanbones_humanbone_v1_0_free(memory, &data->rightMiddleIntermediate);
	cgltf_vrmc_vrm_humanoid_humanbones_humanbone_v1_0_free(memory, &data->rightMiddleDistal);
	cgltf_vrmc_vrm_humanoid_humanbones_humanbone_v1_0_free(memory, &data->rightRingProximal);
	cgltf_vrmc_vrm_humanoid_humanbones_humanbone_v1_0_free(memory, &data->rightRingIntermediate);
	cgltf_vrmc_vrm_humanoid_humanbones_humanbone_v1_0_free(memory, &data->rightRingDistal);
	cgltf_vrmc_vrm_humanoid_humanbones_humanbone_v1_0_free(memory, &data->rightLittleProximal);
	cgltf_vrmc_vrm_humanoid_humanbones_humanbone_v1_0_free(memory, &data->rightLittleIntermediate);
	cgltf_vrmc_vrm_humanoid_humanbones_humanbone_v1_0_free(memory, &data->rightLittleDistal);
}

static void cgltf_vrmc_vrm_humanoid_v1_0_free(const struct cgltf_memory_options* memory, cgltf_vrmc_vrm_humanoid_v1_0* data) {
	cgltf_vrmc_vrm_humanoid_humanbones_v1_0_free(memory, &data->humanBones);
}

static void cgltf_vrmc_vrm_lookatrangemap_v1_0_free(const struct cgltf_memory_options* memory, cgltf_vrmc_vrm_lookatrangemap_v1_0* data) {
	(void)memory;
	(void)data;
}

static void cgltf_vrmc_vrm_lookat_v1_0_free(const struct cgltf_memory_options* memory, cgltf_vrmc_vrm_lookat_v1_0* data) {
	memory->free(memory->user_data, data->offsetFromHeadBone);
	cgltf_vrmc_vrm_lookatrangemap_v1_0_free(memory, &data->lookAtHorizontalInner);
	cgltf_vrmc_vrm_lookatrangemap_v1_0_free(memory, &data->lookAtHorizontalOuter);
	cgltf_vrmc_vrm_lookatrangemap_v1_0_free(memory, &data->lookAtVerticalDown);
	cgltf_vrmc_vrm_lookatrangemap_v1_0_free(memory, &data->lookAtVerticalUp);
}

static void cgltf_vrmc_vrm_meta_v1_0_free(const struct cgltf_memory_options* memory, cgltf_vrmc_vrm_meta_v1_0* data) {
	memory->free(memory->user_data, data->name);
	memory->free(memory->user_data, data->version);
	for (cgltf_size i = 0; i < data->authors_count; i++) {
		memory->free(memory->user_data, &data->authors[i]);
	}
	memory->free(memory->user_data, data->authors);
	memory->free(memory->user_data, data->copyrights);
	memory->free(memory->user_data, data->contactInformation);
	memory->free(memory->user_data, data->reference);
	memory->free(memory->user_data, data->otherPermissionUrl);
	memory->free(memory->user_data, data->otherLicenseUrl);
}

static void cgltf_vrmc_vrm_v1_0_free(const struct cgltf_memory_options* memory, cgltf_vrmc_vrm_v1_0* data) {
	memory->free(memory->user_data, data->specVersion);
	cgltf_vrmc_vrm_meta_v1_0_free(memory, &data->meta);
	cgltf_vrmc_vrm_humanoid_v1_0_free(memory, &data->humanoid);
	cgltf_vrmc_vrm_firstperson_v1_0_free(memory, &data->firstPerson);
	cgltf_vrmc_vrm_lookat_v1_0_free(memory, &data->lookAt);
	cgltf_vrmc_vrm_blendshape_v1_0_free(memory, &data->blendShape);
}
static cgltf_bool select_cgltf_vrmc_vrm_blendshape_blendshapegroup_materialvalue_type_v1_0(const char* name, cgltf_vrmc_vrm_blendshape_blendshapegroup_materialvalue_type_v1_0* out) {
	if (strlen(name) == 0) {
		return 0;
	} else if (strlen(name) == 5 && strncmp(name, "color", 5) == 0) {
		*out = cgltf_vrmc_vrm_blendshape_blendshapegroup_materialvalue_type_v1_0_color;
		return 1;
	} else if (strlen(name) == 13 && strncmp(name, "emissionColor", 13) == 0) {
		*out = cgltf_vrmc_vrm_blendshape_blendshapegroup_materialvalue_type_v1_0_emissionColor;
		return 1;
	} else if (strlen(name) == 10 && strncmp(name, "shadeColor", 10) == 0) {
		*out = cgltf_vrmc_vrm_blendshape_blendshapegroup_materialvalue_type_v1_0_shadeColor;
		return 1;
	} else if (strlen(name) == 8 && strncmp(name, "rimColor", 8) == 0) {
		*out = cgltf_vrmc_vrm_blendshape_blendshapegroup_materialvalue_type_v1_0_rimColor;
		return 1;
	} else if (strlen(name) == 12 && strncmp(name, "outlineColor", 12) == 0) {
		*out = cgltf_vrmc_vrm_blendshape_blendshapegroup_materialvalue_type_v1_0_outlineColor;
		return 1;
	}
	return 0;
}

static cgltf_bool select_cgltf_vrmc_vrm_blendshape_blendshapegroup_preset_v1_0(const char* name, cgltf_vrmc_vrm_blendshape_blendshapegroup_preset_v1_0* out) {
	if (strlen(name) == 0) {
		return 0;
	} else if (strlen(name) == 6 && strncmp(name, "custom", 6) == 0) {
		*out = cgltf_vrmc_vrm_blendshape_blendshapegroup_preset_v1_0_custom;
		return 1;
	} else if (strlen(name) == 2 && strncmp(name, "aa", 2) == 0) {
		*out = cgltf_vrmc_vrm_blendshape_blendshapegroup_preset_v1_0_aa;
		return 1;
	} else if (strlen(name) == 2 && strncmp(name, "ih", 2) == 0) {
		*out = cgltf_vrmc_vrm_blendshape_blendshapegroup_preset_v1_0_ih;
		return 1;
	} else if (strlen(name) == 2 && strncmp(name, "ou", 2) == 0) {
		*out = cgltf_vrmc_vrm_blendshape_blendshapegroup_preset_v1_0_ou;
		return 1;
	} else if (strlen(name) == 2 && strncmp(name, "ee", 2) == 0) {
		*out = cgltf_vrmc_vrm_blendshape_blendshapegroup_preset_v1_0_ee;
		return 1;
	} else if (strlen(name) == 2 && strncmp(name, "oh", 2) == 0) {
		*out = cgltf_vrmc_vrm_blendshape_blendshapegroup_preset_v1_0_oh;
		return 1;
	} else if (strlen(name) == 5 && strncmp(name, "blink", 5) == 0) {
		*out = cgltf_vrmc_vrm_blendshape_blendshapegroup_preset_v1_0_blink;
		return 1;
	} else if (strlen(name) == 3 && strncmp(name, "joy", 3) == 0) {
		*out = cgltf_vrmc_vrm_blendshape_blendshapegroup_preset_v1_0_joy;
		return 1;
	} else if (strlen(name) == 5 && strncmp(name, "angry", 5) == 0) {
		*out = cgltf_vrmc_vrm_blendshape_blendshapegroup_preset_v1_0_angry;
		return 1;
	} else if (strlen(name) == 6 && strncmp(name, "sorrow", 6) == 0) {
		*out = cgltf_vrmc_vrm_blendshape_blendshapegroup_preset_v1_0_sorrow;
		return 1;
	} else if (strlen(name) == 3 && strncmp(name, "fun", 3) == 0) {
		*out = cgltf_vrmc_vrm_blendshape_blendshapegroup_preset_v1_0_fun;
		return 1;
	} else if (strlen(name) == 6 && strncmp(name, "lookUp", 6) == 0) {
		*out = cgltf_vrmc_vrm_blendshape_blendshapegroup_preset_v1_0_lookUp;
		return 1;
	} else if (strlen(name) == 8 && strncmp(name, "lookDown", 8) == 0) {
		*out = cgltf_vrmc_vrm_blendshape_blendshapegroup_preset_v1_0_lookDown;
		return 1;
	} else if (strlen(name) == 8 && strncmp(name, "lookLeft", 8) == 0) {
		*out = cgltf_vrmc_vrm_blendshape_blendshapegroup_preset_v1_0_lookLeft;
		return 1;
	} else if (strlen(name) == 9 && strncmp(name, "lookRight", 9) == 0) {
		*out = cgltf_vrmc_vrm_blendshape_blendshapegroup_preset_v1_0_lookRight;
		return 1;
	} else if (strlen(name) == 9 && strncmp(name, "blinkLeft", 9) == 0) {
		*out = cgltf_vrmc_vrm_blendshape_blendshapegroup_preset_v1_0_blinkLeft;
		return 1;
	} else if (strlen(name) == 10 && strncmp(name, "blinkRight", 10) == 0) {
		*out = cgltf_vrmc_vrm_blendshape_blendshapegroup_preset_v1_0_blinkRight;
		return 1;
	} else if (strlen(name) == 7 && strncmp(name, "neutral", 7) == 0) {
		*out = cgltf_vrmc_vrm_blendshape_blendshapegroup_preset_v1_0_neutral;
		return 1;
	}
	return 0;
}

static cgltf_bool select_cgltf_vrmc_vrm_firstperson_meshannotation_firstPersonType_v1_0(const char* name, cgltf_vrmc_vrm_firstperson_meshannotation_firstPersonType_v1_0* out) {
	if (strlen(name) == 0) {
		return 0;
	} else if (strlen(name) == 4 && strncmp(name, "auto", 4) == 0) {
		*out = cgltf_vrmc_vrm_firstperson_meshannotation_firstPersonType_v1_0_auto;
		return 1;
	} else if (strlen(name) == 4 && strncmp(name, "both", 4) == 0) {
		*out = cgltf_vrmc_vrm_firstperson_meshannotation_firstPersonType_v1_0_both;
		return 1;
	} else if (strlen(name) == 15 && strncmp(name, "thirdPersonOnly", 15) == 0) {
		*out = cgltf_vrmc_vrm_firstperson_meshannotation_firstPersonType_v1_0_thirdPersonOnly;
		return 1;
	} else if (strlen(name) == 15 && strncmp(name, "firstPersonOnly", 15) == 0) {
		*out = cgltf_vrmc_vrm_firstperson_meshannotation_firstPersonType_v1_0_firstPersonOnly;
		return 1;
	}
	return 0;
}

static cgltf_bool select_cgltf_vrmc_vrm_lookat_lookAtType_v1_0(const char* name, cgltf_vrmc_vrm_lookat_lookAtType_v1_0* out) {
	if (strlen(name) == 0) {
		return 0;
	} else if (strlen(name) == 4 && strncmp(name, "bone", 4) == 0) {
		*out = cgltf_vrmc_vrm_lookat_lookAtType_v1_0_bone;
		return 1;
	} else if (strlen(name) == 10 && strncmp(name, "blendShape", 10) == 0) {
		*out = cgltf_vrmc_vrm_lookat_lookAtType_v1_0_blendShape;
		return 1;
	}
	return 0;
}

static cgltf_bool select_cgltf_vrmc_vrm_meta_avatarPermission_v1_0(const char* name, cgltf_vrmc_vrm_meta_avatarPermission_v1_0* out) {
	if (strlen(name) == 0) {
		return 0;
	} else if (strlen(name) == 10 && strncmp(name, "OnlyAuthor", 10) == 0) {
		*out = cgltf_vrmc_vrm_meta_avatarPermission_v1_0_OnlyAuthor;
		return 1;
	} else if (strlen(name) == 24 && strncmp(name, "ExplicitlyLicensedPerson", 24) == 0) {
		*out = cgltf_vrmc_vrm_meta_avatarPermission_v1_0_ExplicitlyLicensedPerson;
		return 1;
	} else if (strlen(name) == 8 && strncmp(name, "Everyone", 8) == 0) {
		*out = cgltf_vrmc_vrm_meta_avatarPermission_v1_0_Everyone;
		return 1;
	}
	return 0;
}

static cgltf_bool select_cgltf_vrmc_vrm_meta_commercialUsage_v1_0(const char* name, cgltf_vrmc_vrm_meta_commercialUsage_v1_0* out) {
	if (strlen(name) == 0) {
		return 0;
	} else if (strlen(name) == 30 && strncmp(name, "PersonalNonCommercialNonProfit", 30) == 0) {
		*out = cgltf_vrmc_vrm_meta_commercialUsage_v1_0_PersonalNonCommercialNonProfit;
		return 1;
	} else if (strlen(name) == 27 && strncmp(name, "PersonalNonCommercialProfit", 27) == 0) {
		*out = cgltf_vrmc_vrm_meta_commercialUsage_v1_0_PersonalNonCommercialProfit;
		return 1;
	} else if (strlen(name) == 18 && strncmp(name, "PersonalCommercial", 18) == 0) {
		*out = cgltf_vrmc_vrm_meta_commercialUsage_v1_0_PersonalCommercial;
		return 1;
	} else if (strlen(name) == 11 && strncmp(name, "Corporation", 11) == 0) {
		*out = cgltf_vrmc_vrm_meta_commercialUsage_v1_0_Corporation;
		return 1;
	}
	return 0;
}

static cgltf_bool select_cgltf_vrmc_vrm_meta_creditNotation_v1_0(const char* name, cgltf_vrmc_vrm_meta_creditNotation_v1_0* out) {
	if (strlen(name) == 0) {
		return 0;
	} else if (strlen(name) == 8 && strncmp(name, "Required", 8) == 0) {
		*out = cgltf_vrmc_vrm_meta_creditNotation_v1_0_Required;
		return 1;
	} else if (strlen(name) == 11 && strncmp(name, "Unnecessary", 11) == 0) {
		*out = cgltf_vrmc_vrm_meta_creditNotation_v1_0_Unnecessary;
		return 1;
	} else if (strlen(name) == 9 && strncmp(name, "Abandoned", 9) == 0) {
		*out = cgltf_vrmc_vrm_meta_creditNotation_v1_0_Abandoned;
		return 1;
	}
	return 0;
}

static cgltf_bool select_cgltf_vrmc_vrm_meta_modify_v1_0(const char* name, cgltf_vrmc_vrm_meta_modify_v1_0* out) {
	if (strlen(name) == 0) {
		return 0;
	} else if (strlen(name) == 10 && strncmp(name, "Prohibited", 10) == 0) {
		*out = cgltf_vrmc_vrm_meta_modify_v1_0_Prohibited;
		return 1;
	} else if (strlen(name) == 9 && strncmp(name, "Inherited", 9) == 0) {
		*out = cgltf_vrmc_vrm_meta_modify_v1_0_Inherited;
		return 1;
	} else if (strlen(name) == 12 && strncmp(name, "NotInherited", 12) == 0) {
		*out = cgltf_vrmc_vrm_meta_modify_v1_0_NotInherited;
		return 1;
	}
	return 0;
}
static int cgltf_parse_json_vrmc_vrm_springbone_collidergroup_collider_v1_0(cgltf_options* options, jsmntok_t const* tokens, int i, const uint8_t* json_chunk, cgltf_vrmc_vrm_springbone_collidergroup_collider_v1_0* out_data) {
	(void)options;
	if (tokens[i].type == JSMN_OBJECT) {
		int size = tokens[i].size; ++i;
		for (int j = 0; j < size; ++j) {
			if (tokens[i].type != JSMN_STRING || tokens[i].size == 0) {
				continue;
			} else if (cgltf_json_strcmp(tokens + i, json_chunk, "offset") == 0) {
				i = cgltf_parse_json_array(options, tokens, i + 1, json_chunk, sizeof(cgltf_float), (void**)&out_data->offset, &out_data->offset_count);
				if (i < 0) return i;
				i = cgltf_parse_json_float_array(tokens, i - 1, json_chunk, out_data->offset, (int)out_data->offset_count);
			} else if (cgltf_json_strcmp(tokens + i, json_chunk, "radius") == 0) {
				++i; out_data->radius = cgltf_json_to_float(tokens + i, json_chunk); ++i;
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
static int cgltf_parse_json_vrmc_vrm_springbone_bonegroup_v1_0(cgltf_options* options, jsmntok_t const* tokens, int i, const uint8_t* json_chunk, cgltf_vrmc_vrm_springbone_bonegroup_v1_0* out_data) {
	(void)options;
	if (tokens[i].type == JSMN_OBJECT) {
		int size = tokens[i].size; ++i;
		for (int j = 0; j < size; ++j) {
			if (tokens[i].type != JSMN_STRING || tokens[i].size == 0) {
				continue;
			} else if (cgltf_json_strcmp(tokens + i, json_chunk, "name") == 0) {
				i = cgltf_parse_json_string(options, tokens, i + 1, json_chunk, &out_data->name);
			} else if (cgltf_json_strcmp(tokens + i, json_chunk, "stiffness") == 0) {
				++i; out_data->stiffness = cgltf_json_to_float(tokens + i, json_chunk); ++i;
			} else if (cgltf_json_strcmp(tokens + i, json_chunk, "gravityPower") == 0) {
				++i; out_data->gravityPower = cgltf_json_to_float(tokens + i, json_chunk); ++i;
			} else if (cgltf_json_strcmp(tokens + i, json_chunk, "gravityDir") == 0) {
				i = cgltf_parse_json_array(options, tokens, i + 1, json_chunk, sizeof(cgltf_float), (void**)&out_data->gravityDir, &out_data->gravityDir_count);
				if (i < 0) return i;
				i = cgltf_parse_json_float_array(tokens, i - 1, json_chunk, out_data->gravityDir, (int)out_data->gravityDir_count);
			} else if (cgltf_json_strcmp(tokens + i, json_chunk, "dragForce") == 0) {
				++i; out_data->dragForce = cgltf_json_to_float(tokens + i, json_chunk); ++i;
			} else if (cgltf_json_strcmp(tokens + i, json_chunk, "center") == 0) {
				++i; out_data->center = cgltf_json_to_int(tokens + i, json_chunk); ++i;
			} else if (cgltf_json_strcmp(tokens + i, json_chunk, "hitRadius") == 0) {
				++i; out_data->hitRadius = cgltf_json_to_float(tokens + i, json_chunk); ++i;
			} else if (cgltf_json_strcmp(tokens + i, json_chunk, "bones") == 0) {
				i = cgltf_parse_json_array(options, tokens, i + 1, json_chunk, sizeof(cgltf_int), (void**)&out_data->bones, &out_data->bones_count);
				if (i < 0) return i;
				i = cgltf_parse_json_int_array(tokens, i - 1, json_chunk, out_data->bones, (int)out_data->bones_count);
			} else if (cgltf_json_strcmp(tokens + i, json_chunk, "colliderGroups") == 0) {
				i = cgltf_parse_json_array(options, tokens, i + 1, json_chunk, sizeof(cgltf_int), (void**)&out_data->colliderGroups, &out_data->colliderGroups_count);
				if (i < 0) return i;
				i = cgltf_parse_json_int_array(tokens, i - 1, json_chunk, out_data->colliderGroups, (int)out_data->colliderGroups_count);
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
static int cgltf_parse_json_vrmc_vrm_springbone_collidergroup_v1_0(cgltf_options* options, jsmntok_t const* tokens, int i, const uint8_t* json_chunk, cgltf_vrmc_vrm_springbone_collidergroup_v1_0* out_data) {
	(void)options;
	if (tokens[i].type == JSMN_OBJECT) {
		int size = tokens[i].size; ++i;
		for (int j = 0; j < size; ++j) {
			if (tokens[i].type != JSMN_STRING || tokens[i].size == 0) {
				continue;
			} else if (cgltf_json_strcmp(tokens + i, json_chunk, "node") == 0) {
				++i; out_data->node = cgltf_json_to_int(tokens + i, json_chunk); ++i;
			} else if (cgltf_json_strcmp(tokens + i, json_chunk, "colliders") == 0) {
				i = cgltf_parse_json_array(options, tokens, i + 1, json_chunk, sizeof(cgltf_vrmc_vrm_springbone_collidergroup_collider_v1_0), (void**)&out_data->colliders, &out_data->colliders_count);
				if (i < 0) return i;
				for (cgltf_size k = 0; k < out_data->colliders_count; k++) {
					i = cgltf_parse_json_vrmc_vrm_springbone_collidergroup_collider_v1_0(options, tokens, i, json_chunk, out_data->colliders + k);
				}
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
static int cgltf_parse_json_vrmc_vrm_springbone_v1_0(cgltf_options* options, jsmntok_t const* tokens, int i, const uint8_t* json_chunk, cgltf_vrmc_vrm_springbone_v1_0* out_data) {
	(void)options;
	if (tokens[i].type == JSMN_OBJECT) {
		int size = tokens[i].size; ++i;
		for (int j = 0; j < size; ++j) {
			if (tokens[i].type != JSMN_STRING || tokens[i].size == 0) {
				continue;
			} else if (cgltf_json_strcmp(tokens + i, json_chunk, "boneGroups") == 0) {
				i = cgltf_parse_json_array(options, tokens, i + 1, json_chunk, sizeof(cgltf_vrmc_vrm_springbone_bonegroup_v1_0), (void**)&out_data->boneGroups, &out_data->boneGroups_count);
				if (i < 0) return i;
				for (cgltf_size k = 0; k < out_data->boneGroups_count; k++) {
					i = cgltf_parse_json_vrmc_vrm_springbone_bonegroup_v1_0(options, tokens, i, json_chunk, out_data->boneGroups + k);
				}
			} else if (cgltf_json_strcmp(tokens + i, json_chunk, "colliderGroups") == 0) {
				i = cgltf_parse_json_array(options, tokens, i + 1, json_chunk, sizeof(cgltf_vrmc_vrm_springbone_collidergroup_v1_0), (void**)&out_data->colliderGroups, &out_data->colliderGroups_count);
				if (i < 0) return i;
				for (cgltf_size k = 0; k < out_data->colliderGroups_count; k++) {
					i = cgltf_parse_json_vrmc_vrm_springbone_collidergroup_v1_0(options, tokens, i, json_chunk, out_data->colliderGroups + k);
				}
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
static int cgltf_parse_json_vrmc_vrm_blendshape_blendshapegroup_blendshapebind_v1_0(cgltf_options* options, jsmntok_t const* tokens, int i, const uint8_t* json_chunk, cgltf_vrmc_vrm_blendshape_blendshapegroup_blendshapebind_v1_0* out_data) {
	(void)options;
	if (tokens[i].type == JSMN_OBJECT) {
		int size = tokens[i].size; ++i;
		for (int j = 0; j < size; ++j) {
			if (tokens[i].type != JSMN_STRING || tokens[i].size == 0) {
				continue;
			} else if (cgltf_json_strcmp(tokens + i, json_chunk, "node") == 0) {
				i = cgltf_parse_json_string(options, tokens, i + 1, json_chunk, &out_data->node);
			} else if (cgltf_json_strcmp(tokens + i, json_chunk, "index") == 0) {
				i = cgltf_parse_json_string(options, tokens, i + 1, json_chunk, &out_data->index);
			} else if (cgltf_json_strcmp(tokens + i, json_chunk, "weight") == 0) {
				++i; out_data->weight = cgltf_json_to_float(tokens + i, json_chunk); ++i;
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
static int cgltf_parse_json_vrmc_vrm_blendshape_blendshapegroup_materialuvbind_v1_0(cgltf_options* options, jsmntok_t const* tokens, int i, const uint8_t* json_chunk, cgltf_vrmc_vrm_blendshape_blendshapegroup_materialuvbind_v1_0* out_data) {
	(void)options;
	if (tokens[i].type == JSMN_OBJECT) {
		int size = tokens[i].size; ++i;
		for (int j = 0; j < size; ++j) {
			if (tokens[i].type != JSMN_STRING || tokens[i].size == 0) {
				continue;
			} else if (cgltf_json_strcmp(tokens + i, json_chunk, "material") == 0) {
				++i; out_data->material = cgltf_json_to_int(tokens + i, json_chunk); ++i;
			} else if (cgltf_json_strcmp(tokens + i, json_chunk, "scaling") == 0) {
				i = cgltf_parse_json_array(options, tokens, i + 1, json_chunk, sizeof(cgltf_float), (void**)&out_data->scaling, &out_data->scaling_count);
				if (i < 0) return i;
				i = cgltf_parse_json_float_array(tokens, i - 1, json_chunk, out_data->scaling, (int)out_data->scaling_count);
			} else if (cgltf_json_strcmp(tokens + i, json_chunk, "offset") == 0) {
				i = cgltf_parse_json_array(options, tokens, i + 1, json_chunk, sizeof(cgltf_float), (void**)&out_data->offset, &out_data->offset_count);
				if (i < 0) return i;
				i = cgltf_parse_json_float_array(tokens, i - 1, json_chunk, out_data->offset, (int)out_data->offset_count);
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
static int cgltf_parse_json_vrmc_vrm_blendshape_blendshapegroup_materialvalue_v1_0(cgltf_options* options, jsmntok_t const* tokens, int i, const uint8_t* json_chunk, cgltf_vrmc_vrm_blendshape_blendshapegroup_materialvalue_v1_0* out_data) {
	(void)options;
	if (tokens[i].type == JSMN_OBJECT) {
		int size = tokens[i].size; ++i;
		for (int j = 0; j < size; ++j) {
			if (tokens[i].type != JSMN_STRING || tokens[i].size == 0) {
				continue;
			} else if (cgltf_json_strcmp(tokens + i, json_chunk, "material") == 0) {
				++i; out_data->material = cgltf_json_to_int(tokens + i, json_chunk); ++i;
			} else if (cgltf_json_strcmp(tokens + i, json_chunk, "type") == 0) {
				char* enum_key = NULL; i = cgltf_parse_json_string(options, tokens, i + 1, json_chunk, &enum_key);
				i = select_cgltf_vrmc_vrm_blendshape_blendshapegroup_materialvalue_type_v1_0(enum_key, &out_data->type) ? i : -1;
			} else if (cgltf_json_strcmp(tokens + i, json_chunk, "targetValue") == 0) {
				i = cgltf_parse_json_array(options, tokens, i + 1, json_chunk, sizeof(cgltf_float), (void**)&out_data->targetValue, &out_data->targetValue_count);
				if (i < 0) return i;
				i = cgltf_parse_json_float_array(tokens, i - 1, json_chunk, out_data->targetValue, (int)out_data->targetValue_count);
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
static int cgltf_parse_json_vrmc_vrm_blendshape_blendshapegroup_v1_0(cgltf_options* options, jsmntok_t const* tokens, int i, const uint8_t* json_chunk, cgltf_vrmc_vrm_blendshape_blendshapegroup_v1_0* out_data) {
	(void)options;
	if (tokens[i].type == JSMN_OBJECT) {
		int size = tokens[i].size; ++i;
		for (int j = 0; j < size; ++j) {
			if (tokens[i].type != JSMN_STRING || tokens[i].size == 0) {
				continue;
			} else if (cgltf_json_strcmp(tokens + i, json_chunk, "name") == 0) {
				i = cgltf_parse_json_string(options, tokens, i + 1, json_chunk, &out_data->name);
			} else if (cgltf_json_strcmp(tokens + i, json_chunk, "preset") == 0) {
				char* enum_key = NULL; i = cgltf_parse_json_string(options, tokens, i + 1, json_chunk, &enum_key);
				i = select_cgltf_vrmc_vrm_blendshape_blendshapegroup_preset_v1_0(enum_key, &out_data->preset) ? i : -1;
			} else if (cgltf_json_strcmp(tokens + i, json_chunk, "binds") == 0) {
				i = cgltf_parse_json_array(options, tokens, i + 1, json_chunk, sizeof(cgltf_vrmc_vrm_blendshape_blendshapegroup_blendshapebind_v1_0), (void**)&out_data->binds, &out_data->binds_count);
				if (i < 0) return i;
				for (cgltf_size k = 0; k < out_data->binds_count; k++) {
					i = cgltf_parse_json_vrmc_vrm_blendshape_blendshapegroup_blendshapebind_v1_0(options, tokens, i, json_chunk, out_data->binds + k);
				}
			} else if (cgltf_json_strcmp(tokens + i, json_chunk, "materialValues") == 0) {
				i = cgltf_parse_json_array(options, tokens, i + 1, json_chunk, sizeof(cgltf_vrmc_vrm_blendshape_blendshapegroup_materialvalue_v1_0), (void**)&out_data->materialValues, &out_data->materialValues_count);
				if (i < 0) return i;
				for (cgltf_size k = 0; k < out_data->materialValues_count; k++) {
					i = cgltf_parse_json_vrmc_vrm_blendshape_blendshapegroup_materialvalue_v1_0(options, tokens, i, json_chunk, out_data->materialValues + k);
				}
			} else if (cgltf_json_strcmp(tokens + i, json_chunk, "materialUVBinds") == 0) {
				i = cgltf_parse_json_array(options, tokens, i + 1, json_chunk, sizeof(cgltf_vrmc_vrm_blendshape_blendshapegroup_materialuvbind_v1_0), (void**)&out_data->materialUVBinds, &out_data->materialUVBinds_count);
				if (i < 0) return i;
				for (cgltf_size k = 0; k < out_data->materialUVBinds_count; k++) {
					i = cgltf_parse_json_vrmc_vrm_blendshape_blendshapegroup_materialuvbind_v1_0(options, tokens, i, json_chunk, out_data->materialUVBinds + k);
				}
			} else if (cgltf_json_strcmp(tokens + i, json_chunk, "isBinary") == 0) {
				++i; out_data->isBinary = cgltf_json_to_bool(tokens + i, json_chunk); ++i;
			} else if (cgltf_json_strcmp(tokens + i, json_chunk, "ignoreBlink") == 0) {
				++i; out_data->ignoreBlink = cgltf_json_to_bool(tokens + i, json_chunk); ++i;
			} else if (cgltf_json_strcmp(tokens + i, json_chunk, "ignoreLookAt") == 0) {
				++i; out_data->ignoreLookAt = cgltf_json_to_bool(tokens + i, json_chunk); ++i;
			} else if (cgltf_json_strcmp(tokens + i, json_chunk, "ignoreMouth") == 0) {
				++i; out_data->ignoreMouth = cgltf_json_to_bool(tokens + i, json_chunk); ++i;
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
static int cgltf_parse_json_vrmc_vrm_blendshape_v1_0(cgltf_options* options, jsmntok_t const* tokens, int i, const uint8_t* json_chunk, cgltf_vrmc_vrm_blendshape_v1_0* out_data) {
	(void)options;
	if (tokens[i].type == JSMN_OBJECT) {
		int size = tokens[i].size; ++i;
		for (int j = 0; j < size; ++j) {
			if (tokens[i].type != JSMN_STRING || tokens[i].size == 0) {
				continue;
			} else if (cgltf_json_strcmp(tokens + i, json_chunk, "blendShapeGroups") == 0) {
				i = cgltf_parse_json_array(options, tokens, i + 1, json_chunk, sizeof(cgltf_vrmc_vrm_blendshape_blendshapegroup_v1_0), (void**)&out_data->blendShapeGroups, &out_data->blendShapeGroups_count);
				if (i < 0) return i;
				for (cgltf_size k = 0; k < out_data->blendShapeGroups_count; k++) {
					i = cgltf_parse_json_vrmc_vrm_blendshape_blendshapegroup_v1_0(options, tokens, i, json_chunk, out_data->blendShapeGroups + k);
				}
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
static int cgltf_parse_json_vrmc_vrm_constraint_v1_0(cgltf_options* options, jsmntok_t const* tokens, int i, const uint8_t* json_chunk, cgltf_vrmc_vrm_constraint_v1_0* out_data) {
	(void)options;
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
static int cgltf_parse_json_vrmc_vrm_firstperson_meshannotation_v1_0(cgltf_options* options, jsmntok_t const* tokens, int i, const uint8_t* json_chunk, cgltf_vrmc_vrm_firstperson_meshannotation_v1_0* out_data) {
	(void)options;
	if (tokens[i].type == JSMN_OBJECT) {
		int size = tokens[i].size; ++i;
		for (int j = 0; j < size; ++j) {
			if (tokens[i].type != JSMN_STRING || tokens[i].size == 0) {
				continue;
			} else if (cgltf_json_strcmp(tokens + i, json_chunk, "node") == 0) {
				i = cgltf_parse_json_string(options, tokens, i + 1, json_chunk, &out_data->node);
			} else if (cgltf_json_strcmp(tokens + i, json_chunk, "firstPersonType") == 0) {
				char* enum_key = NULL; i = cgltf_parse_json_string(options, tokens, i + 1, json_chunk, &enum_key);
				i = select_cgltf_vrmc_vrm_firstperson_meshannotation_firstPersonType_v1_0(enum_key, &out_data->firstPersonType) ? i : -1;
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
static int cgltf_parse_json_vrmc_vrm_firstperson_v1_0(cgltf_options* options, jsmntok_t const* tokens, int i, const uint8_t* json_chunk, cgltf_vrmc_vrm_firstperson_v1_0* out_data) {
	(void)options;
	if (tokens[i].type == JSMN_OBJECT) {
		int size = tokens[i].size; ++i;
		for (int j = 0; j < size; ++j) {
			if (tokens[i].type != JSMN_STRING || tokens[i].size == 0) {
				continue;
			} else if (cgltf_json_strcmp(tokens + i, json_chunk, "meshAnnotations") == 0) {
				i = cgltf_parse_json_array(options, tokens, i + 1, json_chunk, sizeof(cgltf_vrmc_vrm_firstperson_meshannotation_v1_0), (void**)&out_data->meshAnnotations, &out_data->meshAnnotations_count);
				if (i < 0) return i;
				for (cgltf_size k = 0; k < out_data->meshAnnotations_count; k++) {
					i = cgltf_parse_json_vrmc_vrm_firstperson_meshannotation_v1_0(options, tokens, i, json_chunk, out_data->meshAnnotations + k);
				}
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
static int cgltf_parse_json_vrmc_vrm_humanoid_humanbones_humanbone_v1_0(cgltf_options* options, jsmntok_t const* tokens, int i, const uint8_t* json_chunk, cgltf_vrmc_vrm_humanoid_humanbones_humanbone_v1_0* out_data) {
	(void)options;
	if (tokens[i].type == JSMN_OBJECT) {
		int size = tokens[i].size; ++i;
		for (int j = 0; j < size; ++j) {
			if (tokens[i].type != JSMN_STRING || tokens[i].size == 0) {
				continue;
			} else if (cgltf_json_strcmp(tokens + i, json_chunk, "node") == 0) {
				++i; out_data->node = cgltf_json_to_int(tokens + i, json_chunk); ++i;
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
static int cgltf_parse_json_vrmc_vrm_humanoid_humanbones_v1_0(cgltf_options* options, jsmntok_t const* tokens, int i, const uint8_t* json_chunk, cgltf_vrmc_vrm_humanoid_humanbones_v1_0* out_data) {
	(void)options;
	if (tokens[i].type == JSMN_OBJECT) {
		int size = tokens[i].size; ++i;
		for (int j = 0; j < size; ++j) {
			if (tokens[i].type != JSMN_STRING || tokens[i].size == 0) {
				continue;
			} else if (cgltf_json_strcmp(tokens + i, json_chunk, "hips") == 0) {
				i = cgltf_parse_json_vrmc_vrm_humanoid_humanbones_humanbone_v1_0(options, tokens, i + 1, json_chunk, &out_data->hips);
			} else if (cgltf_json_strcmp(tokens + i, json_chunk, "spine") == 0) {
				i = cgltf_parse_json_vrmc_vrm_humanoid_humanbones_humanbone_v1_0(options, tokens, i + 1, json_chunk, &out_data->spine);
			} else if (cgltf_json_strcmp(tokens + i, json_chunk, "chest") == 0) {
				i = cgltf_parse_json_vrmc_vrm_humanoid_humanbones_humanbone_v1_0(options, tokens, i + 1, json_chunk, &out_data->chest);
			} else if (cgltf_json_strcmp(tokens + i, json_chunk, "upperChest") == 0) {
				i = cgltf_parse_json_vrmc_vrm_humanoid_humanbones_humanbone_v1_0(options, tokens, i + 1, json_chunk, &out_data->upperChest);
			} else if (cgltf_json_strcmp(tokens + i, json_chunk, "neck") == 0) {
				i = cgltf_parse_json_vrmc_vrm_humanoid_humanbones_humanbone_v1_0(options, tokens, i + 1, json_chunk, &out_data->neck);
			} else if (cgltf_json_strcmp(tokens + i, json_chunk, "head") == 0) {
				i = cgltf_parse_json_vrmc_vrm_humanoid_humanbones_humanbone_v1_0(options, tokens, i + 1, json_chunk, &out_data->head);
			} else if (cgltf_json_strcmp(tokens + i, json_chunk, "leftEye") == 0) {
				i = cgltf_parse_json_vrmc_vrm_humanoid_humanbones_humanbone_v1_0(options, tokens, i + 1, json_chunk, &out_data->leftEye);
			} else if (cgltf_json_strcmp(tokens + i, json_chunk, "rightEye") == 0) {
				i = cgltf_parse_json_vrmc_vrm_humanoid_humanbones_humanbone_v1_0(options, tokens, i + 1, json_chunk, &out_data->rightEye);
			} else if (cgltf_json_strcmp(tokens + i, json_chunk, "jaw") == 0) {
				i = cgltf_parse_json_vrmc_vrm_humanoid_humanbones_humanbone_v1_0(options, tokens, i + 1, json_chunk, &out_data->jaw);
			} else if (cgltf_json_strcmp(tokens + i, json_chunk, "leftUpperLeg") == 0) {
				i = cgltf_parse_json_vrmc_vrm_humanoid_humanbones_humanbone_v1_0(options, tokens, i + 1, json_chunk, &out_data->leftUpperLeg);
			} else if (cgltf_json_strcmp(tokens + i, json_chunk, "leftLowerLeg") == 0) {
				i = cgltf_parse_json_vrmc_vrm_humanoid_humanbones_humanbone_v1_0(options, tokens, i + 1, json_chunk, &out_data->leftLowerLeg);
			} else if (cgltf_json_strcmp(tokens + i, json_chunk, "leftFoot") == 0) {
				i = cgltf_parse_json_vrmc_vrm_humanoid_humanbones_humanbone_v1_0(options, tokens, i + 1, json_chunk, &out_data->leftFoot);
			} else if (cgltf_json_strcmp(tokens + i, json_chunk, "leftToes") == 0) {
				i = cgltf_parse_json_vrmc_vrm_humanoid_humanbones_humanbone_v1_0(options, tokens, i + 1, json_chunk, &out_data->leftToes);
			} else if (cgltf_json_strcmp(tokens + i, json_chunk, "rightUpperLeg") == 0) {
				i = cgltf_parse_json_vrmc_vrm_humanoid_humanbones_humanbone_v1_0(options, tokens, i + 1, json_chunk, &out_data->rightUpperLeg);
			} else if (cgltf_json_strcmp(tokens + i, json_chunk, "rightLowerLeg") == 0) {
				i = cgltf_parse_json_vrmc_vrm_humanoid_humanbones_humanbone_v1_0(options, tokens, i + 1, json_chunk, &out_data->rightLowerLeg);
			} else if (cgltf_json_strcmp(tokens + i, json_chunk, "rightFoot") == 0) {
				i = cgltf_parse_json_vrmc_vrm_humanoid_humanbones_humanbone_v1_0(options, tokens, i + 1, json_chunk, &out_data->rightFoot);
			} else if (cgltf_json_strcmp(tokens + i, json_chunk, "rightToes") == 0) {
				i = cgltf_parse_json_vrmc_vrm_humanoid_humanbones_humanbone_v1_0(options, tokens, i + 1, json_chunk, &out_data->rightToes);
			} else if (cgltf_json_strcmp(tokens + i, json_chunk, "leftShoulder") == 0) {
				i = cgltf_parse_json_vrmc_vrm_humanoid_humanbones_humanbone_v1_0(options, tokens, i + 1, json_chunk, &out_data->leftShoulder);
			} else if (cgltf_json_strcmp(tokens + i, json_chunk, "leftUpperArm") == 0) {
				i = cgltf_parse_json_vrmc_vrm_humanoid_humanbones_humanbone_v1_0(options, tokens, i + 1, json_chunk, &out_data->leftUpperArm);
			} else if (cgltf_json_strcmp(tokens + i, json_chunk, "leftLowerArm") == 0) {
				i = cgltf_parse_json_vrmc_vrm_humanoid_humanbones_humanbone_v1_0(options, tokens, i + 1, json_chunk, &out_data->leftLowerArm);
			} else if (cgltf_json_strcmp(tokens + i, json_chunk, "leftHand") == 0) {
				i = cgltf_parse_json_vrmc_vrm_humanoid_humanbones_humanbone_v1_0(options, tokens, i + 1, json_chunk, &out_data->leftHand);
			} else if (cgltf_json_strcmp(tokens + i, json_chunk, "rightShoulder") == 0) {
				i = cgltf_parse_json_vrmc_vrm_humanoid_humanbones_humanbone_v1_0(options, tokens, i + 1, json_chunk, &out_data->rightShoulder);
			} else if (cgltf_json_strcmp(tokens + i, json_chunk, "rightUpperArm") == 0) {
				i = cgltf_parse_json_vrmc_vrm_humanoid_humanbones_humanbone_v1_0(options, tokens, i + 1, json_chunk, &out_data->rightUpperArm);
			} else if (cgltf_json_strcmp(tokens + i, json_chunk, "rightLowerArm") == 0) {
				i = cgltf_parse_json_vrmc_vrm_humanoid_humanbones_humanbone_v1_0(options, tokens, i + 1, json_chunk, &out_data->rightLowerArm);
			} else if (cgltf_json_strcmp(tokens + i, json_chunk, "rightHand") == 0) {
				i = cgltf_parse_json_vrmc_vrm_humanoid_humanbones_humanbone_v1_0(options, tokens, i + 1, json_chunk, &out_data->rightHand);
			} else if (cgltf_json_strcmp(tokens + i, json_chunk, "leftThumbProximal") == 0) {
				i = cgltf_parse_json_vrmc_vrm_humanoid_humanbones_humanbone_v1_0(options, tokens, i + 1, json_chunk, &out_data->leftThumbProximal);
			} else if (cgltf_json_strcmp(tokens + i, json_chunk, "leftThumbIntermediate") == 0) {
				i = cgltf_parse_json_vrmc_vrm_humanoid_humanbones_humanbone_v1_0(options, tokens, i + 1, json_chunk, &out_data->leftThumbIntermediate);
			} else if (cgltf_json_strcmp(tokens + i, json_chunk, "leftThumbDistal") == 0) {
				i = cgltf_parse_json_vrmc_vrm_humanoid_humanbones_humanbone_v1_0(options, tokens, i + 1, json_chunk, &out_data->leftThumbDistal);
			} else if (cgltf_json_strcmp(tokens + i, json_chunk, "leftIndexProximal") == 0) {
				i = cgltf_parse_json_vrmc_vrm_humanoid_humanbones_humanbone_v1_0(options, tokens, i + 1, json_chunk, &out_data->leftIndexProximal);
			} else if (cgltf_json_strcmp(tokens + i, json_chunk, "leftIndexIntermediate") == 0) {
				i = cgltf_parse_json_vrmc_vrm_humanoid_humanbones_humanbone_v1_0(options, tokens, i + 1, json_chunk, &out_data->leftIndexIntermediate);
			} else if (cgltf_json_strcmp(tokens + i, json_chunk, "leftIndexDistal") == 0) {
				i = cgltf_parse_json_vrmc_vrm_humanoid_humanbones_humanbone_v1_0(options, tokens, i + 1, json_chunk, &out_data->leftIndexDistal);
			} else if (cgltf_json_strcmp(tokens + i, json_chunk, "leftMiddleProximal") == 0) {
				i = cgltf_parse_json_vrmc_vrm_humanoid_humanbones_humanbone_v1_0(options, tokens, i + 1, json_chunk, &out_data->leftMiddleProximal);
			} else if (cgltf_json_strcmp(tokens + i, json_chunk, "leftMiddleIntermediate") == 0) {
				i = cgltf_parse_json_vrmc_vrm_humanoid_humanbones_humanbone_v1_0(options, tokens, i + 1, json_chunk, &out_data->leftMiddleIntermediate);
			} else if (cgltf_json_strcmp(tokens + i, json_chunk, "leftMiddleDistal") == 0) {
				i = cgltf_parse_json_vrmc_vrm_humanoid_humanbones_humanbone_v1_0(options, tokens, i + 1, json_chunk, &out_data->leftMiddleDistal);
			} else if (cgltf_json_strcmp(tokens + i, json_chunk, "leftRingProximal") == 0) {
				i = cgltf_parse_json_vrmc_vrm_humanoid_humanbones_humanbone_v1_0(options, tokens, i + 1, json_chunk, &out_data->leftRingProximal);
			} else if (cgltf_json_strcmp(tokens + i, json_chunk, "leftRingIntermediate") == 0) {
				i = cgltf_parse_json_vrmc_vrm_humanoid_humanbones_humanbone_v1_0(options, tokens, i + 1, json_chunk, &out_data->leftRingIntermediate);
			} else if (cgltf_json_strcmp(tokens + i, json_chunk, "leftRingDistal") == 0) {
				i = cgltf_parse_json_vrmc_vrm_humanoid_humanbones_humanbone_v1_0(options, tokens, i + 1, json_chunk, &out_data->leftRingDistal);
			} else if (cgltf_json_strcmp(tokens + i, json_chunk, "leftLittleProximal") == 0) {
				i = cgltf_parse_json_vrmc_vrm_humanoid_humanbones_humanbone_v1_0(options, tokens, i + 1, json_chunk, &out_data->leftLittleProximal);
			} else if (cgltf_json_strcmp(tokens + i, json_chunk, "leftLittleIntermediate") == 0) {
				i = cgltf_parse_json_vrmc_vrm_humanoid_humanbones_humanbone_v1_0(options, tokens, i + 1, json_chunk, &out_data->leftLittleIntermediate);
			} else if (cgltf_json_strcmp(tokens + i, json_chunk, "leftLittleDistal") == 0) {
				i = cgltf_parse_json_vrmc_vrm_humanoid_humanbones_humanbone_v1_0(options, tokens, i + 1, json_chunk, &out_data->leftLittleDistal);
			} else if (cgltf_json_strcmp(tokens + i, json_chunk, "rightThumbProximal") == 0) {
				i = cgltf_parse_json_vrmc_vrm_humanoid_humanbones_humanbone_v1_0(options, tokens, i + 1, json_chunk, &out_data->rightThumbProximal);
			} else if (cgltf_json_strcmp(tokens + i, json_chunk, "rightThumbIntermediate") == 0) {
				i = cgltf_parse_json_vrmc_vrm_humanoid_humanbones_humanbone_v1_0(options, tokens, i + 1, json_chunk, &out_data->rightThumbIntermediate);
			} else if (cgltf_json_strcmp(tokens + i, json_chunk, "rightThumbDistal") == 0) {
				i = cgltf_parse_json_vrmc_vrm_humanoid_humanbones_humanbone_v1_0(options, tokens, i + 1, json_chunk, &out_data->rightThumbDistal);
			} else if (cgltf_json_strcmp(tokens + i, json_chunk, "rightIndexProximal") == 0) {
				i = cgltf_parse_json_vrmc_vrm_humanoid_humanbones_humanbone_v1_0(options, tokens, i + 1, json_chunk, &out_data->rightIndexProximal);
			} else if (cgltf_json_strcmp(tokens + i, json_chunk, "rightIndexIntermediate") == 0) {
				i = cgltf_parse_json_vrmc_vrm_humanoid_humanbones_humanbone_v1_0(options, tokens, i + 1, json_chunk, &out_data->rightIndexIntermediate);
			} else if (cgltf_json_strcmp(tokens + i, json_chunk, "rightIndexDistal") == 0) {
				i = cgltf_parse_json_vrmc_vrm_humanoid_humanbones_humanbone_v1_0(options, tokens, i + 1, json_chunk, &out_data->rightIndexDistal);
			} else if (cgltf_json_strcmp(tokens + i, json_chunk, "rightMiddleProximal") == 0) {
				i = cgltf_parse_json_vrmc_vrm_humanoid_humanbones_humanbone_v1_0(options, tokens, i + 1, json_chunk, &out_data->rightMiddleProximal);
			} else if (cgltf_json_strcmp(tokens + i, json_chunk, "rightMiddleIntermediate") == 0) {
				i = cgltf_parse_json_vrmc_vrm_humanoid_humanbones_humanbone_v1_0(options, tokens, i + 1, json_chunk, &out_data->rightMiddleIntermediate);
			} else if (cgltf_json_strcmp(tokens + i, json_chunk, "rightMiddleDistal") == 0) {
				i = cgltf_parse_json_vrmc_vrm_humanoid_humanbones_humanbone_v1_0(options, tokens, i + 1, json_chunk, &out_data->rightMiddleDistal);
			} else if (cgltf_json_strcmp(tokens + i, json_chunk, "rightRingProximal") == 0) {
				i = cgltf_parse_json_vrmc_vrm_humanoid_humanbones_humanbone_v1_0(options, tokens, i + 1, json_chunk, &out_data->rightRingProximal);
			} else if (cgltf_json_strcmp(tokens + i, json_chunk, "rightRingIntermediate") == 0) {
				i = cgltf_parse_json_vrmc_vrm_humanoid_humanbones_humanbone_v1_0(options, tokens, i + 1, json_chunk, &out_data->rightRingIntermediate);
			} else if (cgltf_json_strcmp(tokens + i, json_chunk, "rightRingDistal") == 0) {
				i = cgltf_parse_json_vrmc_vrm_humanoid_humanbones_humanbone_v1_0(options, tokens, i + 1, json_chunk, &out_data->rightRingDistal);
			} else if (cgltf_json_strcmp(tokens + i, json_chunk, "rightLittleProximal") == 0) {
				i = cgltf_parse_json_vrmc_vrm_humanoid_humanbones_humanbone_v1_0(options, tokens, i + 1, json_chunk, &out_data->rightLittleProximal);
			} else if (cgltf_json_strcmp(tokens + i, json_chunk, "rightLittleIntermediate") == 0) {
				i = cgltf_parse_json_vrmc_vrm_humanoid_humanbones_humanbone_v1_0(options, tokens, i + 1, json_chunk, &out_data->rightLittleIntermediate);
			} else if (cgltf_json_strcmp(tokens + i, json_chunk, "rightLittleDistal") == 0) {
				i = cgltf_parse_json_vrmc_vrm_humanoid_humanbones_humanbone_v1_0(options, tokens, i + 1, json_chunk, &out_data->rightLittleDistal);
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
static int cgltf_parse_json_vrmc_vrm_humanoid_v1_0(cgltf_options* options, jsmntok_t const* tokens, int i, const uint8_t* json_chunk, cgltf_vrmc_vrm_humanoid_v1_0* out_data) {
	(void)options;
	if (tokens[i].type == JSMN_OBJECT) {
		int size = tokens[i].size; ++i;
		for (int j = 0; j < size; ++j) {
			if (tokens[i].type != JSMN_STRING || tokens[i].size == 0) {
				continue;
			} else if (cgltf_json_strcmp(tokens + i, json_chunk, "humanBones") == 0) {
				i = cgltf_parse_json_vrmc_vrm_humanoid_humanbones_v1_0(options, tokens, i + 1, json_chunk, &out_data->humanBones);
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
static int cgltf_parse_json_vrmc_vrm_lookatrangemap_v1_0(cgltf_options* options, jsmntok_t const* tokens, int i, const uint8_t* json_chunk, cgltf_vrmc_vrm_lookatrangemap_v1_0* out_data) {
	(void)options;
	if (tokens[i].type == JSMN_OBJECT) {
		int size = tokens[i].size; ++i;
		for (int j = 0; j < size; ++j) {
			if (tokens[i].type != JSMN_STRING || tokens[i].size == 0) {
				continue;
			} else if (cgltf_json_strcmp(tokens + i, json_chunk, "inputMaxValue") == 0) {
				++i; out_data->inputMaxValue = cgltf_json_to_float(tokens + i, json_chunk); ++i;
			} else if (cgltf_json_strcmp(tokens + i, json_chunk, "outputScale") == 0) {
				++i; out_data->outputScale = cgltf_json_to_float(tokens + i, json_chunk); ++i;
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
static int cgltf_parse_json_vrmc_vrm_lookat_v1_0(cgltf_options* options, jsmntok_t const* tokens, int i, const uint8_t* json_chunk, cgltf_vrmc_vrm_lookat_v1_0* out_data) {
	(void)options;
	if (tokens[i].type == JSMN_OBJECT) {
		int size = tokens[i].size; ++i;
		for (int j = 0; j < size; ++j) {
			if (tokens[i].type != JSMN_STRING || tokens[i].size == 0) {
				continue;
			} else if (cgltf_json_strcmp(tokens + i, json_chunk, "offsetFromHeadBone") == 0) {
				i = cgltf_parse_json_array(options, tokens, i + 1, json_chunk, sizeof(cgltf_float), (void**)&out_data->offsetFromHeadBone, &out_data->offsetFromHeadBone_count);
				if (i < 0) return i;
				i = cgltf_parse_json_float_array(tokens, i - 1, json_chunk, out_data->offsetFromHeadBone, (int)out_data->offsetFromHeadBone_count);
			} else if (cgltf_json_strcmp(tokens + i, json_chunk, "lookAtType") == 0) {
				char* enum_key = NULL; i = cgltf_parse_json_string(options, tokens, i + 1, json_chunk, &enum_key);
				i = select_cgltf_vrmc_vrm_lookat_lookAtType_v1_0(enum_key, &out_data->lookAtType) ? i : -1;
			} else if (cgltf_json_strcmp(tokens + i, json_chunk, "lookAtHorizontalInner") == 0) {
				i = cgltf_parse_json_vrmc_vrm_lookatrangemap_v1_0(options, tokens, i + 1, json_chunk, &out_data->lookAtHorizontalInner);
			} else if (cgltf_json_strcmp(tokens + i, json_chunk, "lookAtHorizontalOuter") == 0) {
				i = cgltf_parse_json_vrmc_vrm_lookatrangemap_v1_0(options, tokens, i + 1, json_chunk, &out_data->lookAtHorizontalOuter);
			} else if (cgltf_json_strcmp(tokens + i, json_chunk, "lookAtVerticalDown") == 0) {
				i = cgltf_parse_json_vrmc_vrm_lookatrangemap_v1_0(options, tokens, i + 1, json_chunk, &out_data->lookAtVerticalDown);
			} else if (cgltf_json_strcmp(tokens + i, json_chunk, "lookAtVerticalUp") == 0) {
				i = cgltf_parse_json_vrmc_vrm_lookatrangemap_v1_0(options, tokens, i + 1, json_chunk, &out_data->lookAtVerticalUp);
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
static int cgltf_parse_json_vrmc_vrm_meta_v1_0(cgltf_options* options, jsmntok_t const* tokens, int i, const uint8_t* json_chunk, cgltf_vrmc_vrm_meta_v1_0* out_data) {
	(void)options;
	if (tokens[i].type == JSMN_OBJECT) {
		int size = tokens[i].size; ++i;
		for (int j = 0; j < size; ++j) {
			if (tokens[i].type != JSMN_STRING || tokens[i].size == 0) {
				continue;
			} else if (cgltf_json_strcmp(tokens + i, json_chunk, "name") == 0) {
				i = cgltf_parse_json_string(options, tokens, i + 1, json_chunk, &out_data->name);
			} else if (cgltf_json_strcmp(tokens + i, json_chunk, "version") == 0) {
				i = cgltf_parse_json_string(options, tokens, i + 1, json_chunk, &out_data->version);
			} else if (cgltf_json_strcmp(tokens + i, json_chunk, "authors") == 0) {
				i = cgltf_parse_json_string_array(options, tokens, i + 1, json_chunk, &out_data->authors, &out_data->authors_count);
			} else if (cgltf_json_strcmp(tokens + i, json_chunk, "copyrights") == 0) {
				i = cgltf_parse_json_string(options, tokens, i + 1, json_chunk, &out_data->copyrights);
			} else if (cgltf_json_strcmp(tokens + i, json_chunk, "contactInformation") == 0) {
				i = cgltf_parse_json_string(options, tokens, i + 1, json_chunk, &out_data->contactInformation);
			} else if (cgltf_json_strcmp(tokens + i, json_chunk, "reference") == 0) {
				i = cgltf_parse_json_string(options, tokens, i + 1, json_chunk, &out_data->reference);
			} else if (cgltf_json_strcmp(tokens + i, json_chunk, "thumbnailImage") == 0) {
				++i; out_data->thumbnailImage = cgltf_json_to_int(tokens + i, json_chunk); ++i;
			} else if (cgltf_json_strcmp(tokens + i, json_chunk, "avatarPermission") == 0) {
				char* enum_key = NULL; i = cgltf_parse_json_string(options, tokens, i + 1, json_chunk, &enum_key);
				i = select_cgltf_vrmc_vrm_meta_avatarPermission_v1_0(enum_key, &out_data->avatarPermission) ? i : -1;
			} else if (cgltf_json_strcmp(tokens + i, json_chunk, "violentUsage") == 0) {
				++i; out_data->violentUsage = cgltf_json_to_bool(tokens + i, json_chunk); ++i;
			} else if (cgltf_json_strcmp(tokens + i, json_chunk, "sexualUsage") == 0) {
				++i; out_data->sexualUsage = cgltf_json_to_bool(tokens + i, json_chunk); ++i;
			} else if (cgltf_json_strcmp(tokens + i, json_chunk, "gameUsage") == 0) {
				++i; out_data->gameUsage = cgltf_json_to_bool(tokens + i, json_chunk); ++i;
			} else if (cgltf_json_strcmp(tokens + i, json_chunk, "commercialUsage") == 0) {
				char* enum_key = NULL; i = cgltf_parse_json_string(options, tokens, i + 1, json_chunk, &enum_key);
				i = select_cgltf_vrmc_vrm_meta_commercialUsage_v1_0(enum_key, &out_data->commercialUsage) ? i : -1;
			} else if (cgltf_json_strcmp(tokens + i, json_chunk, "politicalOrReligiousUsage") == 0) {
				++i; out_data->politicalOrReligiousUsage = cgltf_json_to_bool(tokens + i, json_chunk); ++i;
			} else if (cgltf_json_strcmp(tokens + i, json_chunk, "otherPermissionUrl") == 0) {
				i = cgltf_parse_json_string(options, tokens, i + 1, json_chunk, &out_data->otherPermissionUrl);
			} else if (cgltf_json_strcmp(tokens + i, json_chunk, "creditNotation") == 0) {
				char* enum_key = NULL; i = cgltf_parse_json_string(options, tokens, i + 1, json_chunk, &enum_key);
				i = select_cgltf_vrmc_vrm_meta_creditNotation_v1_0(enum_key, &out_data->creditNotation) ? i : -1;
			} else if (cgltf_json_strcmp(tokens + i, json_chunk, "allowRedistribution") == 0) {
				++i; out_data->allowRedistribution = cgltf_json_to_bool(tokens + i, json_chunk); ++i;
			} else if (cgltf_json_strcmp(tokens + i, json_chunk, "modify") == 0) {
				char* enum_key = NULL; i = cgltf_parse_json_string(options, tokens, i + 1, json_chunk, &enum_key);
				i = select_cgltf_vrmc_vrm_meta_modify_v1_0(enum_key, &out_data->modify) ? i : -1;
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
static int cgltf_parse_json_vrmc_vrm_v1_0(cgltf_options* options, jsmntok_t const* tokens, int i, const uint8_t* json_chunk, cgltf_vrmc_vrm_v1_0* out_data) {
	(void)options;
	if (tokens[i].type == JSMN_OBJECT) {
		int size = tokens[i].size; ++i;
		for (int j = 0; j < size; ++j) {
			if (tokens[i].type != JSMN_STRING || tokens[i].size == 0) {
				continue;
			} else if (cgltf_json_strcmp(tokens + i, json_chunk, "specVersion") == 0) {
				i = cgltf_parse_json_string(options, tokens, i + 1, json_chunk, &out_data->specVersion);
			} else if (cgltf_json_strcmp(tokens + i, json_chunk, "meta") == 0) {
				i = cgltf_parse_json_vrmc_vrm_meta_v1_0(options, tokens, i + 1, json_chunk, &out_data->meta);
			} else if (cgltf_json_strcmp(tokens + i, json_chunk, "humanoid") == 0) {
				i = cgltf_parse_json_vrmc_vrm_humanoid_v1_0(options, tokens, i + 1, json_chunk, &out_data->humanoid);
			} else if (cgltf_json_strcmp(tokens + i, json_chunk, "firstPerson") == 0) {
				i = cgltf_parse_json_vrmc_vrm_firstperson_v1_0(options, tokens, i + 1, json_chunk, &out_data->firstPerson);
			} else if (cgltf_json_strcmp(tokens + i, json_chunk, "lookAt") == 0) {
				i = cgltf_parse_json_vrmc_vrm_lookat_v1_0(options, tokens, i + 1, json_chunk, &out_data->lookAt);
			} else if (cgltf_json_strcmp(tokens + i, json_chunk, "blendShape") == 0) {
				i = cgltf_parse_json_vrmc_vrm_blendshape_v1_0(options, tokens, i + 1, json_chunk, &out_data->blendShape);
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
