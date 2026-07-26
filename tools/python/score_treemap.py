import plotly.graph_objects as go
import re

GLOBAL_ASM_REGEX = r'\#pragma\sGLOBAL_ASM[(]".*(?=\/)\/([^.]+).s"[)]'

class ScoreTreemap:
    def __init__(self, map_file):
        self.map_file = map_file

    def generateTreemapData(self, score_files, code_size, exclude_lib):
        labels = ["Decomp"]
        parents = [None]
        values = [0]
        colours = [None]
        legends = [None]

        for scoreFile in score_files:
            if exclude_lib and '/libultra/' in scoreFile.filepath:
                continue

            parentName = scoreFile.filepath.replace('./src/', '')

            for func in scoreFile.functions:
                color = '#92ac68'
                legend = 'matched'
                if func.is_documented:
                    color = 'green'
                    legend = 'documented'

                labels.append(func.function_name)
                parents.append(parentName)
                values.append(func.size)
                colours.append(color)
                legends.append(legend)

            # Use the stored text from the file
            with open(scoreFile.filepath, 'r') as f:
                text = f.read()
            
            matches = re.finditer(GLOBAL_ASM_REGEX, text, re.MULTILINE)
            for match in matches:
                funcName = match.groups()[0]
                if funcName in self.map_file.function_sizes:
                    size = self.map_file.function_sizes[funcName]

                    color = "grey"
                    legend = "N/A"
                    if funcName in scoreFile.non_matchings:
                        color = 'orange'
                        legend = "non matching"
                    elif funcName in scoreFile.non_equivalents:
                        color = 'red'
                        legend = "non equivalent"

                    labels.append(funcName)
                    parents.append(parentName)
                    values.append(size)
                    colours.append(color)
                    legends.append(legend)

            labels.append(parentName)
            parents.append("Decomp")
            values.append(0)
            colours.append(None)
            legends.append(None)

        return labels, parents, values, colours, legends

    def generateTreemap(self, score_files, output_path, selected_version, code_size, exclude_lib=False):
        print(f"Generating progress treemap, outputting file to {output_path}")

        # Prepare data
        labels, parents, values, colours, legends = self.generateTreemapData(
            score_files, code_size, exclude_lib
        )

        # Calculate statistics for each parent file
        file_stats = {}
        for scoreFile in score_files:
            if exclude_lib and '/libultra/' in scoreFile.filepath:
                continue

            parentName = scoreFile.filepath.replace('./src/', '')
            file_stats[parentName] = {
                'matched': 0,           # Total matched functions
                'documented': 0,        # Only documented functions
                'non matching': 0,
                'non equivalent': 0,
                'N/A': 0
            }

            # Count all matched functions (both documented and non-documented)
            for func in scoreFile.functions:
                file_stats[parentName]['matched'] += 1
                if func.is_documented:
                    file_stats[parentName]['documented'] += 1

            # Count non-matched functions from GLOBAL_ASM
            with open(scoreFile.filepath, 'r') as f:
                text = f.read()
            
            matches = re.finditer(GLOBAL_ASM_REGEX, text, re.MULTILINE)
            for match in matches:
                funcName = match.groups()[0]
                if funcName in self.map_file.function_sizes:
                    if funcName in scoreFile.non_matchings:
                        file_stats[parentName]['non matching'] += 1
                    elif funcName in scoreFile.non_equivalents:
                        file_stats[parentName]['non equivalent'] += 1
                    else:
                        file_stats[parentName]['N/A'] += 1

        # Create custom hover text
        hover_texts = []
        for i, label in enumerate(labels):
            parent = parents[i]
            value = values[i]

            if label == "Decomp":
                hover_texts.append("")
            elif value == 0:
                # Parent nodes (file names) - show statistics
                if label in file_stats:
                    stats = file_stats[label]
                    hover_text = f"<b>{label}</b><br>"

                    stat_lines = []
                    if stats['matched'] > 0:
                        stat_lines.append(f"Decompiled functions: {stats['matched']}")
                    if stats['documented'] > 0:
                        stat_lines.append(f"Documented functions: {stats['documented']}")
                    if stats['non matching'] > 0:
                        stat_lines.append(f"Non matching functions: {stats['non matching']}")
                    if stats['non equivalent'] > 0:
                        stat_lines.append(f"Non equivalent functions: {stats['non equivalent']}")

                    hover_text += "<br>".join(stat_lines)
                    hover_texts.append(hover_text)
                else:
                    hover_texts.append(f"<b>{label}</b>")
            else:
                # Function nodes - show size information
                percent = (value / code_size * 100) if code_size > 0 else 0
                hover_texts.append(f"<b>{label}</b><br>{value} bytes ({percent:.2f}%)")

        # Filter out 0-byte values for the treemap
        display_values = [v if v > 0 else 1 for v in values]

        # Create the treemap figure
        fig = go.Figure(go.Treemap(
            labels=labels,
            parents=parents,
            values=display_values,
            text=hover_texts,
            hovertemplate='%{text}<extra></extra>',
            marker=dict(colors=colours),
            root_color="lightgrey",
            textinfo="none"
        ))

        # Add custom legend using annotations
        legend_items = [
            ("green", "documented"),
            ("#92ac68", "matched"),
            ("orange", "non matching"),
            ("red", "non equivalent"),
            ("grey", "N/A")
        ]

        annotations = []
        for i, (color, label) in enumerate(legend_items):
            annotations.append(dict(
                x=1.1,
                y=1 - (i * 0.05),
                xref="paper",
                yref="paper",
                showarrow=False,
                text=f"<span style='color:{color}'>■</span> {label}",
                font=dict(size=12)
            ))

        fig.update_layout(
            margin=dict(t=50, l=25, r=150, b=25),
            title=f"Decomp Progress [{selected_version}]",
            annotations=annotations
        )

        # Save to HTML file
        fig.write_html(output_path)
        print(f"Treemap saved to {output_path}")
